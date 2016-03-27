if(!exists("get_names", mode="function"))
  source("pollutantmean.R")

pollutantmean <- function(directory, pollutant, id = 1:332) {
  wd <- getwd()
  setwd(directory)
  names <- get_names(id)
  values <- numeric()
  for (name in names) {
    df <- read.csv(name)
    values <- append(values, df[!is.na(df[, pollutant]), pollutant])
  }
  setwd(wd)
  mean(values)
}
