# CJSModels

Fit first-capture-conditional Cormack-Jolly-Seber models in R using
native TMB. Estimate unit-time apparent survival and detection from
encounter histories.

> **Experimental software.** Results are provisional. Development tests
> do not establish parameter recovery, interval coverage or scientific
> maturity. Apparent survival combines mortality and permanent
> emigration.

## Start with a fixed-effects model

Read the [worked
example](https://itchyshin.github.io/CJSModels/articles/cjs-first-capture.md),
then the [data
constructor](https://itchyshin.github.io/CJSModels/reference/cmr_data.md)
and [fitting
function](https://itchyshin.github.io/CJSModels/reference/drm_cjs.md).
Install the development package from a reviewed local source checkout
with `R CMD INSTALL .`; TMB and a C++ compiler are required. No CRAN
release is claimed.

The likelihood conditions on each animal’s first capture. It excludes
all-zero histories and does not estimate abundance or unseen animals.

## Tested scope

The local R full check passed Status OK with 2,280 assertions and two
explained finite-difference warnings. A fresh fixed-effects R/Julia fit
agreed within coefficient 1e-5 and loglikelihood 1e-6 tolerances. These
are bounded numerical and package checks, not all-route parity or
scientific calibration.

Shared and persistent individual effects, process-specific SD predictors
and reference-selection correction are inherited experimental routes.
Their broad extraction-specific fit, output and interval combinations
remain unqualified. Repeated-sampling recovery and interval
coverage/calibration remain deferred. Shared-effect reference selection,
shared-plus-individual combinations and random-effect or selection
bridges are outside the current contract.

## Julia companion

[CJSModels.jl](https://github.com/itchyshin/CJSModels.jl) provides a
standalone Julia API. The optional R bridge uses a separate Julia
environment containing CJSModels and RCall; RCall is not a dependency of
the standalone Julia package. See [bridge
setup](https://itchyshin.github.io/CJSModels/reference/cjs_julia_setup.md)
for the R entry point. The repository is currently private; public
deployment is pending review.
