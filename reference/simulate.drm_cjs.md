# Simulate conditional capture histories from a CJS fit

Simulate conditional capture histories from a CJS fit

## Usage

``` r
# S3 method for class 'drm_cjs'
simulate(object, nsim = 1L, seed = NULL, max_selection_attempts = 100000L, ...)
```

## Arguments

- object:

  A `drm_cjs` fit.

- nsim:

  Number of simulated data sets.

- seed:

  Optional seed. A supplied seed leaves the caller's RNG unchanged.

- max_selection_attempts:

  Maximum reference-law draws per individual while simulating a
  requested first-capture event.

- ...:

  Unused.

## Value

A list of `cmr_simulation` records that can be refitted. Individual-
effect records carry a `simulation` attribute naming the target and
effect draw rule; selection-conditioned records also carry aligned IDs
and eligibility provenance.

## Details

For ordinary individual-effect fits, each history receives fresh
independent process effects that persist across that complete simulated
history. These are conditional marked-cohort replicates given first
capture. Reference-selection fits draw persistent effects from the
reference normal law, simulate from eligibility, and retain draws whose
first capture occurs at each fitted occasion. The maximum attempts are
bounded per individual. SD formulas are evaluated per individual when
their predictors are constant across that individual's fitted history.
