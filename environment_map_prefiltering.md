# Background 
Physical based rendering(PBR) provides unified lighting and material model for real-time rendering. To further achieve photo realistic rendering result with PBR, we need Image based lighting(IBL) to better simulate real-life light sources. However doing all the PBR calculation for IBL light source at runtime is costly due to high amount of incoming lights affecting the specular result. To boost runtime performance, we may bring in specular environment map prefiltering that precomputes contribution of incoming lights from environment map which is available at DCC stage. Surface orientation and roughness affecting specular results are unknown until runtime, so we precomputes many combinations of different surface orientations and roughness and store the results in a mipmapped 2D cubemap -  
- Each mipmap level stores results of a particular roughness value 
- Each texel coordinates stores result of  a particular surface orientation 

View direction also affects specular results, but it is too difficult to introduce additional degree of freedom. We assume the view direction is the same with surface normal. Fresnel effect brought by different view direction can be precomputed and stored in a separate texture for later compensating at runtime. 

# General idea of specular environment map prefiltering 
- For an environment map, we treat each texel as a virtual point light. They lit the position together from different directions. 
- For diffuse lighting, each direction within the hemisphere of the lit position (angle between the light direction and surface normal is less than 90 degrees) contributes to the final diffuse result. We may pre-calculate this irradiance map by sampling the hemisphere evenly for each surface normal and store the result in a cubemap 
- For specular lighting, roughness greatly affects the specular result. If roughness is 0, halfway vector is aligned with the surface normal, and the view reflection direction is the only one contributes to specular radiance. In this case, we may sample the exact incoming direction from the original environment map.  
- When the roughness goes higher, orientation of micro facet on the surface varies, result in disturbance of reflectance light's direction. The direction of the reflection is a normal distribution around the view reflection and its variance goes up with the roughness. We may sampling the environment map at random directions distributed accordingly, and compute their weighted means to approximate the result.  
- Since roughness brings additional degree of freedom, we need to precompute for several different roughness and store them in different mipmap levels. 
- Combination explosion makes it impractical to pre-calculate every view direction for each surface normal, so we assume that the view direction is the same with surface normal.

# Prefiltering shader implementation 
The following shaders are Unreal Engine 4's implementation of environment map prefiltering<sup>[1]</sup> 
PrefilterEnvMap() is the shader function generating prefiltered environment map.  
- For each surface direction (normal N), it samples NumSamples(1024) directions distributed normally around it. 
- Returns output weighted average to approximates convolution of incoming environment lights. 
Auxiliary function ImportanceSampleGGX() generates normal distributed vectors around surface normal N 

        // ImportanceSampleGGX() generates vectors normal distributed around surface normal 
        // Xi is a random 2-dimension number distributed evenly between [0, 1] 
        // Roughness affects distribution's deviation 
        // N is surface normal, mean of the distribution 
        float3 ImportanceSampleGGX( float2 Xi, float Roughness, float3 N ) 
        { 
            float a = Roughness * Roughness; 
            float Phi = 2 * PI * Xi.x; // Azimuth Phi，distributed evenly between [0, 2Pi] 
            float CosTheta = sqrt( (1 - Xi.y) / ( 1 + (a*a - 1) * Xi.y ) ); // Inclination Theta, normally distributed around N 
            float SinTheta = sqrt( 1 - CosTheta * CosTheta ); 
            float3 H; // Halfway vector 

            // Transform azimuth Phi and inclination Theta to direction vector in normal space 
            H.x = SinTheta * cos( Phi ); 
            H.y = SinTheta * sin( Phi ); 
            H.z = CosTheta; 

            // Transform direction vector from normal space to world space 
            float3 UpVector = abs(N.z) < 0.999 ? float3(0,0,1) : float3(1,0,0); 
            float3 TangentX = normalize( cross( UpVector , N ) ); 
            float3 TangentY = cross( N, TangentX ); 
            return TangentX * H.x + TangentY * H.y + N * H.z; 
        }

        // PrefilterEnvMap() generates prefiltered environment map texel values 
        // Roughness is surface roughness (within [0, 1]) 
        // R is specular reflection direction. Assuming view direction is aligned with surface normal, 
        // this is also surface normal and view direction. 
        // Output should stores at texture coordinate R in mipmap level Roughness 
        float3 PrefilterEnvMap(float Roughness, float3 R) 
        { 
            float3 N = R; // N: Surface Normal 
            float3 V = R; // V: View direction, approximate with surface normal 
            float3 PrefilteredColor = 0; 
            const uint NumSamples = 1024; 
            for( uint i = 0; i < NumSamples; i++ ) 
            {
                // Xi: the ith element of a 2-dimension low discrepancy random sequence evenly distributed within [0, 1] generated by Hammersley() 
                float2 Xi = Hammersley( i, NumSamples );  
                // ImportanceSampleGGX() generates halfway vectors normal distributed around surface normal. 
                // Here we approximates angle between outgoing light and view direction with angle between halfway vector and surface normal 
                float3 H = ImportanceSampleGGX( Xi, Roughness , N ); 
                float3 L = 2 * dot( V, H ) * H - V; // Calculates incoming light direction L from halfway vector and view direction 
                float NoL = saturate( dot( N, L ) );  
                if( NoL > 0 ) // Only consider incoming lights within hemisphere. 
                {
                    // Approximate integration with weighted samples  
                    PrefilteredColor += EnvMap.SampleLevel( EnvMapSampler , L, 0 ).rgb * NoL; 
                    TotalWeight += NoL; 
                } 
            } 
            return PrefilteredColor / TotalWeight; 
        }

# Using prefiltered environment map at runtime 
With roughness, surface orientation, view direction available at runtime and prefiltered environment map ready, we are able to compute IBL specular in our shading pipeline. 

        // ApproximateSpecularIBL() computes actual specular result. 
        // SpecularColor: material's specular color. 
        // Roughness: surface roughness. 
        // N: surface normal. 
        // V: view direction. 
        // Output: IBL specular result. 
        float3 ApproximateSpecularIBL( float3 SpecularColor, float Roughness, float3 N, float3 V) 
        { 
            float NoV = saturate( dot( N, V ) ); 
            float3 R = 2 * dot( V, N ) * N - V; 
            // PrefilterEnvMap() samples filtered environment map at mipmap level Roughness * MIPMAP_LEVELS 
            // and texture coordinate R with trilinear sampler. 
            float3 PrefilteredColor = PrefilterEnvMap( Roughness , R ); 
            // IntegrateBRDF() samples another precomputed environment BRDF LUT texture compensating  
            // the rest of IBL specular: Fresnel, self-shadowing, etc. (details omitted) 
            float2 EnvBRDF = IntegrateBRDF( Roughness , NoV ); 
            // Combine prefitering and BRDF parts  
            return PrefilteredColor * ( SpecularColor * EnvBRDF.x + EnvBRDF.y ); 
        } 

# Integration with existing engine 
Prefiltered environment map is generated at DCC stage. We may provide standalone tools that takes environment cubemap as input, and output the filtered mipmapped version. Or we can integrate it in engine editor or 3rd party DCC tools for artists' convenience. If engine's editor already have environment probe mechanism, we should embed prefiltering logic there. For BRDF LUT, we may precompute them given Fresnel of possible materials of the engine. 

At runtime, given a graphics engine supporting PBR materials, it is straight forward to add ApproximateSpecularIBL() function to existing shading pipeline. Material inputs such as SpecularColor, Roughness, surface normal N and view direction V should be already available within the engine's PBR pipeline. 

Below image shows rendering result with prefiltered environment map with different roughness. (Image rendered with Diligent Engine<sup>[2]</sup> , PBR/IBL pipeline ported from Filament<sup>[3]</sup>) 

![Image](./orb.png?raw=true)

# Reference 

[1] [Real Shading in Unreal Engine 4](https://de45xmedrsdbp.cloudfront.net/Resources/files/2013SiggraphPresentationsNotes-26915738.pdf)

[2] [Diligent Engine](https://diligentgraphics.com/diligent-engine/)

[3] [Filament, a real-time physically based renderer](https://google.github.io/filament/)