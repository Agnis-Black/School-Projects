import numpy as np
import matplotlib.pyplot as plt

np.random.seed(1)

#Problem 1

#Problem 1.1
def gini_score(groups, classes):
    '''
    Inputs: 
    groups: 2 lists of examples. Each example is a list, where the last element is the label.
    classes: a list of different class labels (it's simply [0.0, 1.0] in this problem)
    Outputs:
    gini: gini score, a real number
    '''
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return gini

#Problem 1.2
def create_split(index, threshold, datalist):
    '''
    Inputs:
    index: The index of the feature used to split data. It starts from 0.
    threshold: The threshold for the given feature based on which to split the data.
        If an example's feature value is < threshold, then it goes to the left group.
        Otherwise (>= threshold), it goes to the right group.
    datalist: A list of samples. 
    Outputs:
    left: List of samples
    right: List of samples
    '''
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return left, right

#Problem 1.3
def get_best_split(datalist):
    '''
    Inputs:
    datalist: A list of samples. Each sample is a list, the last element is the label.
    Outputs:
    node: A dictionary contains 3 key value pairs, such as: node = {'index': integer, 'value': float, 'groups': a tuple contains two lists of examples}
    Pseudo-code:
    for index in range(#feature): # index is the feature index
    for example in datalist:
        use create_split with (index, example[index]) to divide datalist into two groups
        compute the Gini index for this division
    construct a node with the (index, example[index], groups) that corresponds to the lowest Gini index
    '''
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return node

#Problem 1.4
#Problem 1.4-step 1
def to_terminal(group):
    '''
    Input:
    group: A list of examples. Each example is a list, whose last element is the label.
    Output:
    label: the label indicating the most common class value in the group
    '''
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return label

#Problem 1.4-step 2
def recursive_split(node, max_depth, min_size, depth):
    '''
    Inputs:
    node:  A dictionary contains 3 key value pairs, node = 
            {'index': integer, 'value': float, 'groups': a tuple contains two lists fo samples}
    max_depth: maximum depth of the tree, an integer
    min_size: minimum size of a group, an integer
    depth: tree depth for current node
    Output:
    node: as defined above
    '''
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return node

#Problem 1.4-step 3
def build_tree(train, max_depth, min_size):
    '''
    Inputs:
    - train: Training set, a list of examples. Each example is a list, whose last element is the label.
    - max_depth: maximum depth of the tree, an integer (root has depth 1)
    - min_size: minimum size of a group, an integer
    Output:
    - root: The root node, a recursive dictionary that should carry the whole tree
    '''
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return root

#Problem 1.4-step 4
def predict(root, sample):
    '''
    Inputs:
    root: the root node of the tree. a recursive dictionary that carries the whole tree.
    sample: a list
    Outputs:
    '''
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

#Problem 2
def Problem2():
    '''
    Inputs: 
    Outputs:
    acc: accuracy score, a real number
    f1: f1 score, a real number
    '''
    # load and prepare data
    import pandas as pd
    import urllib.request
    import shutil
    from csv import reader
    from random import seed

    url = 'https://www.cs.uic.edu/~zhangx/teaching/data_banknote_authentication.csv'
    file_name = 'data_banknote_authentication.csv'
    with urllib.request.urlopen(url) as response, open(file_name, 'wb') as out_file:
        shutil.copyfileobj(response, out_file)

    file = open(file_name, "rt")
    lines = reader(file)

    df = pd.read_csv(file_name,
                        sep='\t',
                        header=None)
    df.head()

    from sklearn.metrics import f1_score
    from sklearn.metrics import accuracy_score
    seed(1)

    dataset = list(lines)
    max_depth = 6
    min_size = 10
    num_train = 1000

    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return acc, f1
