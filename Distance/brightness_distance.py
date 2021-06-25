import matplotlib.pyplot as plt
import cv2
import time
import numpy as np
from scipy.optimize import curve_fit
from PIL import Image

def fit_function_1(x, k, c):
    y = k*(x**-2) + c
    return y

def fit_function_2(x, k, c, b):
    y = k*(x**(-b)) + c
    return y

def graph_equation(equation, x_range):
    x = np.array(x_range)
    y = eval(equation)
    plt.plot(x,y)
    plt.show()

def main():
    figure_size = 9
    length = 1
    count = 0
    arr = []
    imgs = ["C:/Users/allen/AnxRobotica_2020/Distance/images/2020-07-29_15-57-39-012#pic001324_2020-07-29_15-58-09.jpg",
            "C:/Users/allen/AnxRobotica_2020/Distance/images/2020-07-29_15-59-11-097#pic001348_2020-07-29_15-59-41.jpg",
            "C:/Users/allen/AnxRobotica_2020/Distance/images/2020-07-29_16-01-17-423#pic001360_2020-07-29_16-01-47.jpg",
            "C:/Users/allen/AnxRobotica_2020/Distance/images/2020-07-29_16-02-43-903#pic001370_2020-07-29_16-03-14.jpg",
            "C:/Users/allen/AnxRobotica_2020/Distance/images/2020-07-29_16-04-06-335#pic001381_2020-07-29_16-04-36.jpg",
            "C:/Users/allen/AnxRobotica_2020/Distance/images/2020-07-29_16-05-48-504#pic001393_2020-07-29_16-06-19.jpg",
            "C:/Users/allen/AnxRobotica_2020/Distance/images/2020-07-29_16-07-05-180#pic001407_2020-07-29_16-07-35.jpg",
            "C:/Users/allen/AnxRobotica_2020/Distance/images/2020-07-29_16-07-51-269#pic001422_2020-07-29_16-08-21.jpg",
            "C:/Users/allen/AnxRobotica_2020/Distance/images/2020-07-29_16-09-05-564#pic001437_2020-07-29_16-09-36.jpg",
            "C:/Users/allen/AnxRobotica_2020/Distance/images/2020-07-29_16-09-49-219#pic001449_2020-07-29_16-10-19.jpg",
            "C:/Users/allen/AnxRobotica_2020/Distance/images/2020-07-29_16-10-54-308#pic001464_2020-07-29_16-11-24.jpg",
            "C:/Users/allen/AnxRobotica_2020/Distance/images/2020-07-29_16-12-10-352#pic001479_2020-07-29_16-12-41.jpg",
            "C:/Users/allen/AnxRobotica_2020/Distance/images/2020-07-29_16-13-08-042#pic001494_2020-07-29_16-13-38.jpg"]

    for i in range(0, 13):
        img_brightness = 0
        img = cv2.imread(imgs[i], 1)
        img = cv2.GaussianBlur(img, (figure_size, figure_size), 0)  # gaussian blur
        img = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
        img_value = img[:, :, 2]

        dim = Image.open(imgs[i])
        width, height = dim.size
        brightness = img_value[int(width/2), int(height/2)]
        print("brightness avg at length " + str(length) + ": " + str(brightness))
        if length>1.5:
            arr.append(brightness)
        length = length + 0.5

    print("graphing...")
    time.sleep(3)

    y = np.array(arr)
    x = np.array([2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7])
    #equation should be kx^-2 + C
    fig = plt.figure()
    plt.plot(x, y)
    fig.suptitle("brightness vs. length away from object", fontsize=20)
    plt.xlabel("length", fontsize=18)
    plt.ylabel("brightness", fontsize=16)
    plt.show()

    params = curve_fit(fit_function_1, x, y)
    [k, c] = params[0]
    print("k = "+ str(k), "c = "+ str(c)) #k = 886.6655438654061 c = 45.170587624253635
    '''
    formula = str(k)+"*(x**-2) +"+ str(c)
    graph_equation(formula, range(-1,8))
    '''

main()



