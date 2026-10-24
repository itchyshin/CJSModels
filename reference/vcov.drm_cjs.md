# Covariance matrix for a conditional CJS fit

Covariance matrix for a conditional CJS fit

## Usage

``` r
# S3 method for class 'drm_cjs'
vcov(object, ...)
```

## Arguments

- object:

  A `drm_cjs` fit.

- ...:

  Unused.

## Value

The fixed-coefficient block of the inverse observed negative-log-
likelihood Hessian. Wald covariance requires converged fits with finite,
nonsingular interior curvature. Individual-effect fits at variance
boundaries and shared-effect fits are not eligible.
