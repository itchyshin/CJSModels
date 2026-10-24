# CJSModels

Fit first-capture-conditional Cormack-Jolly-Seber models in R using native TMB. Estimate unit-time apparent survival and detection from encounter histories.

> **Experimental software.** Results are provisional. Development tests do not establish parameter recovery, interval coverage or scientific maturity. Apparent survival combines mortality and permanent emigration.

## Start with a fixed-effects model

Read the [worked example](articles/cjs-first-capture.html), then the [data constructor](reference/cmr_data.html) and [fitting function](reference/drm_cjs.html). Install from GitHub with `remotes::install_github("itchyshin/CJSModels")`, or from a reviewed local source checkout with `R CMD INSTALL .`; TMB and a C++ compiler are required. No CRAN release is claimed.

The likelihood conditions on each animal's first capture. It excludes all-zero histories and does not estimate abundance or unseen animals.

## Tested scope

See the [tested scope article](articles/tested-scope.html) for check results, route qualifications and deferred work.

## Julia companion

Read the [Julia companion documentation](https://itchyshin.github.io/CJSModels.jl/).

[CJSModels.jl](https://github.com/itchyshin/CJSModels.jl) provides a standalone Julia API. The optional R bridge uses a separate Julia environment containing CJSModels and RCall; RCall is not a dependency of the standalone Julia package. See [bridge setup](reference/cjs_julia_setup.html) for the R entry point. Public development source is available on GitHub. The software remains experimental.
