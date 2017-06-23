Compose engine
==============

1. Depth pre-pass + velocity buffer for dynamic objects into RG channel
2. depth test to EQUAL
3. Forward render opaque in HDR target + normal.R16G16 + (specular)
4. GPU particles (using depth and normal buffers for CD)
5. SSAO + specular occlusion
6. SSR from depth + normal + specular + previous frame (pre-tonemapped) + previous camera for repojection
7. Static reflection map from probes
8. Blend depth + specular + lighting with ssao ssr+srm + fog
9. Particle lighting
10. Downscale blur
11. Transparent objects and particles
12. Temporal AA and motion-blur from velocity map
13. Luminance calc via downscaling HDR target to 2x2 texture
14. Postprocess: heat + bloom + flares + filmic tonemapping from avg texture + color grading
15. UI and film grain
