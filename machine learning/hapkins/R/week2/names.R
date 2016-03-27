get_name <- function(num, len=3) {
  ending <- toString(num)
  begin <- paste(rep("0", len - nchar(ending)), collapse = "")
  paste(begin, ending,".csv", sep = "")
}

get_names <- function(id, directory="") {
  names <- character(length(id))
  sep = "/"
  if (directory=="") {
    sep = ""
  }
  for (i in 1:length(id)) {
    name <- get_name(id[i])
    name <- paste(directory, sep, name, sep="")
    names[i] <- name
  }
  names
}
