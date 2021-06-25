#exec(open('C:/Users/allen/AnxRobotica_2020/Distance/img_filters.py').read())
import cv2
from PIL import Image, ImageFilter

#hsv
img2 = cv2.imread("test_images/allen.jpg", 1)
img2 = cv2.resize(img2, (480, 270))
gray_img2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
hsv_img2 = cv2.cvtColor(img2, cv2.COLOR_BGR2HSV)
hue, saturation, value = hsv_img2[:, :, 0], hsv_img2[:, :, 1], hsv_img2[:, :, 2]
cv2.imshow("RGB", img2)
cv2.waitKey(0)
cv2.imshow("HSV", hsv_img2)
cv2.waitKey(0)
cv2.imshow("hue", hue)
cv2.waitKey(0)
cv2.imshow("saturation", saturation)
cv2.waitKey(0)
cv2.imshow("value", value) #brightness
cv2.waitKey(0)

#https://towardsdatascience.com/image-filters-in-python-26ee938e57d2
figure_size = 9 # the dimension of the x and y axis of the kernal.
cv2.imshow("Original (HSV->RGB)", cv2.cvtColor(hsv_img2, cv2.COLOR_HSV2RGB))
cv2.waitKey(0)

mean_blur = cv2.blur(hsv_img2, (figure_size, figure_size))
cv2.imshow("Mean filter", cv2.cvtColor(mean_blur, cv2.COLOR_HSV2RGB))
cv2.waitKey(0)

gauss_blur = cv2.GaussianBlur(hsv_img2, (figure_size, figure_size),0)
cv2.imshow("Gaussian filter", cv2.cvtColor(gauss_blur, cv2.COLOR_HSV2RGB))
cv2.waitKey(0)

median_blur = cv2.medianBlur(hsv_img2, figure_size)
cv2.imshow("Median filter", cv2.cvtColor(median_blur, cv2.COLOR_HSV2RGB))
cv2.waitKey(0)

cv2.imshow("Gaussian brightness values", gauss_blur[:, :, 2])
cv2.waitKey(0)



