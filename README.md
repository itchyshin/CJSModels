# CJSModels

Experimental first-capture-conditional Cormack–Jolly–Seber models, extracted into a dedicated development package. Apparent survival is conditional on remaining alive and available; detection is conditional on being alive. The first capture conditions the likelihood and is not an ordinary detection contribution.

Install from GitHub with `remotes::install_github("itchyshin/CJSModels")`, or from a source checkout with `R CMD INSTALL .` (R, TMB and a C++ compiler required). The retained API is `cmr_data()` followed by `drm_cjs()`; fit classes retain `drm_cjs` for compatibility. The package does not depend on drmTMB.

```r
library(CJSModels)
y <- rbind(c(1,0,0,0),c(1,0,1,0),c(1,1,0,0),c(1,1,1,0),
           c(1,0,0,1),c(1,0,1,1),c(1,1,0,1),c(1,1,1,1))
d <- cmr_data(y, frequency=c(12,4,8,4,4,4,4,4))
f <- drm_cjs(d, phi=~1, p=~1)
coef(f)
logLik(f)
```

The optional fixed-effects bridge uses JuliaCall and a separate Julia environment containing CJSModels and RCall. From a fresh R session, set `JULIA_HOME` to Julia's `bin` directory and `CJS_JL_PATH` to that bridge environment, then request `engine="julia"`. Setup never installs Julia automatically. Random-effect and selection bridges are unsupported.

Prepare it once from the sibling coordination folder (see [bridge setup](docs/BRIDGE.md)):

```sh
cd "/Users/z3437171/Dropbox/Github Local/CJSModels-project"
JULIA_NUM_THREADS=4 OPENBLAS_NUM_THREADS=1 julia --project=bridge-env -e 'using Pkg; Pkg.develop(path="../CJSModels.jl"); Pkg.add("RCall"); Pkg.instantiate()'
```

RCall stays in `CJSModels-project/bridge-env`, outside the standalone Julia dependencies. Select that environment before JuliaCall initializes. Restart R when changing environments.

See [readiness](docs/READINESS.md) for exact checks and limits. Fixed effects, persistent individual effects with quadrature, and shared effects with Laplace approximation are inherited experimental routes; extraction does not establish route parity, parameter recovery or interval calibration. Shared-effect reference selection remains unsupported. No public release or registry submission has occurred.

`SOURCE-MANIFEST.json` records original source paths, commits, dirty state and file hashes. `inst/COPYRIGHTS` records provenance. R GPL source and Julia MIT source remain separate.

Canonical Dropbox twins: `../CJSModels` and `../CJSModels.jl`. See the [route inventory](docs/ROUTES.md) and [documentation provenance](docs/IMPORT-PROVENANCE.json).

Fixed-effects tutorial: [R worked example](docs/tutorials/cjs-first-capture.Rmd). Full parent route examples remain labeled archive material.

Documentation: [R website](https://itchyshin.github.io/CJSModels/). Public development source and documentation are experimental; no registry release or scientific-maturity claim is made.
