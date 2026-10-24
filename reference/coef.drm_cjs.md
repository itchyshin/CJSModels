# Coefficients from a conditional CJS fit

Coefficients from a conditional CJS fit

## Usage

``` r
# S3 method for class 'drm_cjs'
coef(object, process = c("mean", "phi", "p", "sd_phi", "sd_p", "all"), ...)
```

## Arguments

- object:

  A `drm_cjs` fit.

- process:

  Mean-process coefficients by default; `phi`, `p`, `sd_phi`, `sd_p`, or
  `all` selects explicit parameter blocks. SD coefficients describe log
  random-effect standard deviation.

- ...:

  Unused.

## Value

A named numeric vector on the link scale.
