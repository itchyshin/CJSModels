# Optional fixed-effects bridge

Use Julia >=1.10 and the R package JuliaCall. RCall belongs in a separate Julia environment, outside the standalone Julia package dependencies.

## Prepare the sibling environment

From the Dropbox coordination folder, run once:

```sh
cd "/Users/z3437171/Dropbox/Github Local/CJSModels-project"
JULIA_NUM_THREADS=4 OPENBLAS_NUM_THREADS=1 julia --project=bridge-env -e 'using Pkg; Pkg.develop(path="../CJSModels.jl"); Pkg.add("RCall"); Pkg.instantiate()'
```

If `julia` is absent from PATH, use the local juliaup binary:
`/Users/z3437171/.julia/juliaup/julia-1.10.12+0.aarch64.apple.darwin14/Julia-1.10.app/Contents/Resources/julia/bin/julia`.
This creates or updates `CJSModels-project/bridge-env`, with the developed package pointing to `../CJSModels.jl`. A moved checkout must be developed again. The cleanup environment reuses the earlier resolved dependencies and changes only the developed CJSModels path; it does not modify the archive environment.

## Use from a fresh R session

Install the R twin from its canonical source first, then:

```r
Sys.setenv(
  JULIA_HOME = "/Users/z3437171/.julia/juliaup/julia-1.10.12+0.aarch64.apple.darwin14/Julia-1.10.app/Contents/Resources/julia/bin",
  CJS_JL_PATH = "/Users/z3437171/Dropbox/Github Local/CJSModels-project/bridge-env",
  JULIA_NUM_THREADS = "4", OPENBLAS_NUM_THREADS = "1"
)
library(CJSModels)
cjs_julia_setup()
y <- rbind(c(1,0,0,0),c(1,0,1,0),c(1,1,0,0),c(1,1,1,0),
           c(1,0,0,1),c(1,0,1,1),c(1,1,0,1),c(1,1,1,1))
d <- cmr_data(y, frequency=c(12,4,8,4,4,4,4,4))
fit <- drm_cjs(d, engine="julia")
coef(fit)
logLik(fit)
```

`cjs_julia_setup()` sets JULIA_PROJECT before initializing JuliaCall and never installs Julia. Changing an environment after initialization can mix dependencies, so restart R. If R changes, rebuild RCall in this separate environment using that R installation.

The earlier 44-history native R/Julia fit agrees within coefficient 1e-5 and loglikelihood 1e-6 tolerances. The cleanup smoke rechecks this example against the sibling package. These checks do NOT cover random-effect or selection bridges, all fitting controls, recovery or interval calibration.
