import numpy as np
import scipy.linalg

np.random.seed(1)


#Problem 1
def ex4_1(p, nSample):
    """
    Inputs:
    - p: a real number, which specifies the parameter of Bernoulli
    - nSample: an integer which is the  number of samples to draw

    Output:
    - phat: the estimate of p from the samples
    """
    np.random.seed(1)
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
 
    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)***** 

    return phat


#Problem 2.1
def nrmf(x, mu, sigma):
    '''
    Given mean mu and standard deviation sigma, 
    compute the density of the univariate Gaussian distribution at x.
    Here x can be a vector, and the result should be a vector of the same size, 
    with the i-th element being the density of x[i].    
    Input:
    - x:    a 1-D numpy array specifying where to query the probability density 
    - mu:   a real number specifying the mean of the Gaussian
    - sigma: a real number specifying the standard deviation of the Gaussian
    Outputs:
    - p:  a 1-D numpy array specifying the pdf at each element of x
    '''
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
 
    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return p


#Problem 2.2
def bayes_estimator(x, sigma, priorMean, priorStd):
    '''    
    Compute mu_bayes: the Bayes' estimate of mu by using the equation on slide 8  
    Input:
    - x:    a 1-D numpy array specifying the samples from the Gaussian distribution
    - sigma: a real number specifying the standard deviation of the Gaussian
    - priorMean: a real number specifying the mean of the Gaussian prior on mu
    - priorStd: a real number specifying the standard deviation of the Gaussian prior on mu
    Outputs:
    - mu_post: a real number specifying the Bayes' estimate of mu by using the equation on slide 8
    '''

    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return mu_post


#Problem 3.1
def comp_posterior(mu1, sigma1, p1, mu2, sigma2, xrange):
    """
    Compute the likelihood and posterior proability for x values in xrange
    Inputs:
    - mu1: a real number specifying the mean of Gaussian distribution p(x|C1)
    - sigma1: a real number specifying the standard deviation of Gaussian distribution p(x|C1)
    - p1: a real number in [0, 1] specifying the prior probability of C1, i.e., P(C1)
        P(C2) will be automatically inferred by 1 - p1.
    - mu2: a real number specifying the mean of Gaussian distribution p(x|C2)
    - sigma2: a real number specifying the standard deviation of Gaussian distribution p(x|C2)
    - xrange: a 1-D numpy array specifying the range of x to evaluate likelihood and posterior

    Outputs:
    - l1: a 1-D numpy array in the same size as xrange, recording p(x|C1)
    - post1: a 1-D numpy array in the same size as xrange, recording p(C1|x)
    - l2: a 1-D numpy array in the same size as xrange, recording p(x|C2)
    - post2: a 1-D numpy array in the same size as xrange, recording p(C2|x)  
    """
    np.random.seed(1)

    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return l1, post1, l2, post2


#Problem 3.2
def find_dpoint(mu1, sigma1, p1, mu2, sigma2):
    '''
    Find the discriminant points of two Gaussians
    Inputs:
    - mu1: a real number specifying the mean of Gaussian distribution p(x|C1)
    - sigma1: a real number specifying the standard deviation of Gaussian distribution p(x|C1)
    - p1: a real number in [0, 1] specifying the prior probability of C1, i.e., P(C1)
        P(C2) will be automatically inferred by 1 - p1.
    - mu2: a real number specifying the mean of Gaussian distribution p(x|C2)
    - sigma2: a real number specifying the standard deviation of Gaussian distribution p(x|C2)
    Output:
    - x: a 1-D numpy array with two elements, recording the discriminant points
    '''

    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
  
    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return np.array([x1, x2])


#Problem 5.1
def mvar(x, mu, Sigma):
    '''
    Computes the density function of a multi-variate Gaussian distribution 
        with mean mu and covariance matrix Sigma, evaluated at x.  
    This is The multi-variate version of nrmf.

    Inputs:
    - x: 2-D numpy array specifying where to query the probability density 
    - mu: 1-D numpy array specifying the mean of 2-dimensional normal density (num_dimension)  
    - Sigma: 2-D numpy array specifying the covariance of 2-dimensional normal density (num_dimension, num_dimension)
    Outputs:
    - p: a real number specifying the probability density of x
    '''

    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****  

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return p

#Problem 5.2
def comp_density_grid(x, y, mu, Sigma):
    '''
    Generate the meshgrid of plotting the 2-variable Gaussian density function
    Inputs:
    - x: 1-D numpy array specifying a variable 
    - y: 1-D numpy array specifying a variable 
    ...
    Outputs:
    - X: shaped x by using np.meshgrid (len(y), len(x))
    - Y: shaped y by using np.meshgrid (len(y), len(x))
    - f: 2-D numpy array specifying the probability density of 2-variable Gaussian density (len(y), len(x))
    '''
    X, Y = np.meshgrid(x, y)  # Both X and Y are shaped 
    len_x = np.size(x)
    len_y = np.size(y)
    #f = np.empty_like(X)
    f = np.empty([len_y, len_x])
    for i in range(len_x):
        for j in range(len_y):
            # Next we need to assign the values for the f matrix
            # It is quite tricky. Check out 
            # Manual: https://numpy.org/doc/stable/reference/generated/numpy.meshgrid.html
            # Pay attention to the 'notes' section.
            # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****  
          
            # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****  
    return X, Y, f

#Problem 5.3
def sample_multivariate_normal(mu, Sigma, N):
    '''
    Draw samples from a multivariate Gaussian and then re-estimate its mean and covariance
    Inputs:
    - mu: 1-D numpy array specifying the mean of 2-dimensional normal density (num_dimension)
    - Sigma: 2-D numpy array specifying the covariance of 2-dimensional normal density (num_dimension, num_dimension)
    - N: Integer, the number of samples
    ...
    Outputs:
    - sample: 2-D numpy array of drawn samples from a multivariate Gaussian (num_samples, num_dimension)
    - mean: 1-D numpy array specifying the mean of drawn samples (num_dimension)
    - cov: 2-D numpy array specifying the covariance of drawn samples (num_dimension, num_dimension)
    '''
    np.random.seed(1)

    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
  
    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return sample, mean, cov


#Problem 7.1
def comp_CovList(cov1, cov2):
    '''
    Implement the covariance matrix for the four cases
    Inputs:
    - cov1: the estimate of covariance matrix for the first Gaussian based on samples from it
    - cov2: the estimate of covariance matrix for the second Gaussian based on samples from it
            Note cov1 and cov2 are estimated separately, just like in the standard setting.
    Outputs:
    - cov1List: a list of four entries, where cov1List[k-1] is the estimate of Sigma_1 in the case k
    - cov2List: a list of four entries, where cov2List[k-1] is the estimate of Sigma_2 in the case k
    '''
    cov1List = list()
    cov2List = list()

    for k in range(4):
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
        
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return cov1List, cov2List




