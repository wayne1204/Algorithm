import numpy as np
import sys

def trival_gen(nums):
    pass


def order_gen(coord):
    points = coord * 2
    arr = np.arange(points)

    with open ('%d.in' % points, 'w+') as f:    
        f.write("%d\n" % points)
        print("%d" % points)

        for i in range(coord):
            f.write("%d %d\n" % (arr[i*2], arr[i*2+1]))
            print("%d %d" % (arr[i*2], arr[i*2+1]))

        f.write("0\n")
        print(0)

def intersect_gen(coord):
    points = coord * 2
    arr = np.arange(coord)
    arr2 = arr + coord

    with open ('%d.in' % points, 'w+') as f:    
        f.write("%d\n" % points)
        print("%d" % points)

        for i in range(coord):
            f.write("%d %d\n" % (arr[i], arr2[i]))
            print("%d %d" % (arr[i], arr2[i]))

        f.write("0\n")
        print(0)

def parallel_gen(coord):
    points = coord * 2
    arr = np.arange(coord)
    arr2 = arr + coord

    with open ('%d.in' % points, 'w+') as f:    
        f.write("%d\n" % points)
        print("%d" % points)

        for i in range(coord):
            f.write("%d %d\n" % (arr[i], arr2[-(i+1)]))
            print("%d %d" % (arr[i], arr2[-(i+1)]))

        f.write("0\n")
        print(0)

def gen(coord):
    points = coord * 2
    arr = np.random.permutation(points)
    np.random.seed(87)

    with open ('%d.in' % points, 'w+') as f:    
        f.write("%d\n" % points)
        print("%d" % points)

        for i in range(coord):
            f.write("%d %d\n" % (arr[i*2], arr[i*2+1]))
            print("%d %d" % (arr[i*2], arr[i*2+1]))

        f.write("0\n")
        print(0)


if __name__ == "__main__":
    gen(int(sys.argv[1]))    
    # order_gen(int(sys.argv[1]))    
    # intersect_gen(int(sys.argv[1]))   
    # parallel_gen(int(sys.argv[1]))    