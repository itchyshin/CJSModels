# Optional fixed-effects bridge

Use Julia >=1.10 and JuliaCall. In a separate bridge Julia environment, develop the standalone CJSModels.jl package and add RCall. Do not add RCall to CJSModels.jl itself.

Select the bridge environment before Julia initializes, in a fresh R session:

```r
Sys.setenv(JULIA_HOME = "/path/to/julia/bin",
           CJS_JL_PATH = "/path/to/bridge-env")
library(CJSModels)
fit <- drm_cjs(data, engine = "julia")
```

`cjs_julia_setup()` selects JULIA_PROJECT before loading JuliaCall. It does not install Julia. Prepare the bridge environment before use; JuliaCall manages its own RCall setup. Restart R before changing Julia environments.

The bounded 2026-10-24 check compared the R TMB engine with the native Julia matrix bridge on 44 replicated histories. The two coefficient vectors agreed within 1e-5 and log likelihoods within 1e-6 (both approximately -86.99874). This checks one fixed-effects fit. It does NOT cover random-effect bridges, selection bridges, all fitting controls, or inference calibration.
