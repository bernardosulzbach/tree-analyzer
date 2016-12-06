#!/usr/bin/env Rscript

library(xtable)
options(xtable.timestamp="")
options(xtable.include.rownames=FALSE)
options(xtable.table.placement="H")

toString <- function(vec) {
    vec <- replace(format(vec, big.mark=",", scientific=FALSE), is.na(vec), "-")
}

bakeResults <- function(filename, prefix="") {
    data <- read.csv(file=filename, sep=",", head=TRUE)

    bakeColumns <- function(BSTIndex, AVLIndex) {
        table <- data[, c(1, BSTIndex, AVLIndex)]

        label <- names(data[BSTIndex])
        label <- gsub("BST\\.", "", label)
        label <- gsub("\\.", " ", label)
        texName <- tolower(paste(prefix, gsub(" ", "-", label), ".tex", sep=""))

        alignment <- "|r|r|r|r|"

        # Add the time unit if needed.
        label <- gsub("(Insertion|Query|Removal) ", "", label)
        if (label == "Duration") {
            label <- paste(label, " (ms)")
            # Also change zeros to NAs.
            table[table == 0] <- NA
        }
        # Do not calculate ratios in factors.
        if (label != "Factor") {
            # Wait after changing zero times to NAs to calculate factors.
            table <- data.frame(table, table[,2] / table[,3])
            table[4][table[4] == 0] <- NA
            colnames(table)[4] <- "Ratio"
            alignment <- "|r|r|r|r|r|"
        }
        colnames(table)[2] <- paste("BST", label)
        colnames(table)[3] <- paste("AVL", label)
        # Nothing here is Inf, it should be NA.
        table[table == Inf] <- NA

        table[1] <- toString(table[1])
        table[2] <- toString(table[2])
        table[3] <- toString(table[3])

        xtab <- xtable(table, latex.environments="center", align=alignment)
        print(xtab, file=texName, NA.string="-")
        # print(xtab, file=texName, tabular.environment="tabularx", NA.string="-")
    }

    for (i in c(2, 3, 4, 5, 10, 11, 12, 13, 18, 19, 20, 21)) {
        bakeColumns(i, i + 4)
    }
}

bakeResults("result.txt.csv")
bakeResults("result.txt.sorted.csv", "sorted-")
