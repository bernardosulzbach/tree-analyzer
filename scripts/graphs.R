#!/usr/bin/env Rscript
source("loglogplot.r")

data <- read.csv(file="result.txt.csv",sep=",",head=TRUE)
x <- data[, 1]
# xlab <- names(data[1])
xlab <- "Elements"  # Better than the "ID" we are exporting.
ylab <- names(data[2])
yBST <- data[, 2]
yAVL <- data[, 4]
yCombined <- c(yBST, yAVL)

png('rplot.png', width=800, height=500)

# spl <- smooth.spline(x, y, spar=1)
# plot(x, log(y))
# lines(predict(spl, x))

# matplot(data[, 1], data[, -1] + 0.00001, type="l", log="y")

# Disable X axis, we will do it manually later.
lx <- log10(x)
lyBST <- log(yBST + 1)
lyAVL <- log(yAVL + 1)
lyJoined <- log(yCombined + 1)
# lo <- loess(ly~lx)
# fit3 <- lm(ly~poly(lx,3,raw=TRUE)
plot(lx, lyBST, pch=19, col="darkgreen", xaxt="n", xlab=xlab, yaxt="n", ylab=ylab)
points(lx, lyAVL, pch=19, col="purple")
axis(side=1, at=lx, labels=x)
axis(side=2, at=lyJoined, labels=yCombined)

# lines(predict(lo), col='red', lwd=2)
# xx = seq(0, 6, length=7)
# lines(xx, predict(fit3, data.frame(x=xx)), col="purple")

dev.off();
