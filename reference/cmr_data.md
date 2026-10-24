# Validate and store capture histories for conditional CJS models

Validate and store capture histories for conditional CJS models

## Usage

``` r
cmr_data(
  histories,
  id = NULL,
  observed = NULL,
  occasions = NULL,
  intervals = NULL,
  units = "occasion",
  end = NULL,
  frequency = 1L
)
```

## Arguments

- histories:

  Numeric/logical encounter matrix, individuals in rows and ordered
  occasions in columns. `NA` is allowed only where `observed` is
  `FALSE`.

- id:

  Optional unique individual identifiers.

- observed:

  Optional logical matrix marking surveyed encounters.

- occasions:

  Strictly increasing numeric occasion values. Their differences define
  occasion order; use `intervals` to supply model-time lengths
  independently.

- intervals:

  Positive finite interval lengths between occasions.

- units:

  Non-empty string naming the time unit used by `intervals`, such as
  `"years"`. Interval lengths are already expressed in this unit.

- end:

  Optional 1-based administrative endpoint per individual. It is
  follow-up truncation, never the last sighting.

- frequency:

  Positive integer history replication counts.

## Value

A validated `cmr_data` object.

## Examples

``` r
cmr_data(rbind(c(1, 0, 1), c(0, 1, 0)))
```
