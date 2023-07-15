# R Project Version 2
# Graphing a Normal Distribution

# Part 1.
# (C1)
xvals1 <- seq(-3.3,3.3,0.01)

# (C2)
yvals1 <- dnorm(xvals1)

# (C3)
plot(xvals1, yvals1,
     type = "l", 
     main= "Standard Normal Density Function", 
     xlab = "Standard Normal Variable",
     ylab = "Density",
     col = "blue")
# (Graph 1)


# Part 2.
# CDF where X ~ N(mean = 300, var = 196)

# (C4)
xvals2 <- seq(250,350,0.1)

# (C5)
yvals2 <- pnorm(xvals2,300,sqrt(196),TRUE)

# (C6)
plot(xvals2, yvals2,
     type = "l", 
     main= "Normal CDF Function", 
     xlab = "Normal Variable",
     ylab = "Cumulative Probability",
     col = "gray")

# (C7)
cumul_prob <- c(0.025, 0.25, 0.50, 0.75, 0.975)

# (C8)
abline(h = cumul_prob, 
       lty = 2,
       col = "red")

# (C9)
quant <- qnorm(cumul_prob,300,14,TRUE)

# (C10)
abline(v = quant, 
       lty = 1,
       col = "blue")
# (Graph 2)


# (Q1)
# Approximate largest value is 0.4

# (Q2)
# My Standard Normal Density Function is symmetrical
# and bell-shaped. It is not skewed.

# (Q3)
# No, they do not stop at ±3.3. The tails go on until
# ±infinity. As to why the tails do not stop
# at ±3.3, this has to do with the properties of
# Normal distribution relative to a normal population.
# A normal population can be infinitely large to adjust to
# any sample of distribution.

# (Q4)
# x values represents z-scores.

# (Q5)
# y values approach 1.0 as x goes to +infinity,
# y values approach 0 as x goes to -infinity.

# (Q6)
# The point of intersection represents the X value and its
# respective cumulative probability. P(X ≤ xvalue) = yvalue

# (Q7)
# 0.75
