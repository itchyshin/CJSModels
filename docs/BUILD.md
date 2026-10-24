# Build the R documentation locally

From the package root, install the package and the optional documentation tools (pkgdown and rmarkdown). Pandoc must be on PATH. Then run:

```sh
R CMD INSTALL .
Rscript -e 'pkgdown::check_pkgdown(); pkgdown::build_site(new_process=FALSE, install=FALSE, examples=FALSE)'
```

The output goes to `site/`, which is ignored by Git and excluded from the package archive. Reader articles under `vignettes/articles` are website content and are excluded from the installed package. The archived parent article and diagnostic logs under docs are not published by this build.

The configured GitHub Pages URL is a planned deployment target, not evidence of a live site. The verified static bundle is published from `gh-pages` using GitHub Pages. No custom deployment workflow is installed. Review and explicit publication authorization are required before pushing or publishing. Public documentation scope does not authorize changing the private repository visibility.
