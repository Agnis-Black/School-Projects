# R Project 4 Version 10

# (C 1)
size = 29

# (C 2)
prob = 0.33

# (C 3)
num_successes <- c( 0 : size )

# (C 4)
probabilities <- c( dbinom ( num_successes, size, prob ) )

# (C 5)
successes <- factor ( num_successes [ 1 : ( size + 1 ) ] )

# (C 6)
barplot(probabilities,
        main = "Binomial Probabilities (PMF)",
        xlab = "Successes",
        ylab = "Binomial Probabilities (PMF)",
        names.arg = successes,
        ylim = c(0,.16) )

# Part 2 

# (C 7)
set.seed(2222)
sample_values <- rbinom(40,size,prob)
sample_values

# Q1
# Expected value = np, 
# where n = sample size, p = probability of success
expected_value <- size * prob
# Answer : 9.57

# Q2
# Standard distribution of distribution is given as square root of variance
# variance = npq, where q = 1 - p
standard_deviation <- sqrt( size * prob * ( 1 - prob ) )
# Answer : 2.532173

# Q3
mean(sample_values)
# Answer : 10.175

# Q4
sd(sample_values)
# Answer : 2.925463

# Q5
# Answer : sample values data were obtained at random, 
# the distribution on the other hand shows the 
# possible values in an interval and 
# how often they occur(likelihood of outcome)

# Q6
# expected value of success = np
# expected value of failure = nq
expected_value # from Q1
expected_failure <- size * ( 1 - prob )
# Answer : expected number of success = 9.57
# expected number of failure = 19.43
# Approximation to Normal Distribution would work because 
# both values are greater than 5
