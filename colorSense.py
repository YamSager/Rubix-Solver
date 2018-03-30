import argparse
import imutils
import cv2
import numpy as np
import os

def color(image, c):
    mask = np.zeros(image.shape[:2], dtype="uint8")
    cv2.drawContours(mask, [c], -1, 255, -1)
    mask = cv2.erode(mask, None, iterations=2)
    mean = cv2.mean(image, mask=mask)[:3]
    minDist = 450
    minColor = ""
    colors = [("Black", 70, 70, 70), ("Red", 165, 35, 25), ("Blue", 15, 115, 205), ("Green", 65, 190, 105), ("Yellow", 220, 245, 115), ("Orange", 255, 125, 95), ("White", 230, 230, 245)]
    for color in colors:
        square = 0
        for i in range(3):
            square += (-mean[2 -  i] + color[i + 1]) * (-mean[2 - i] + color[i + 1])
        square = np.sqrt(square)
        if square < minDist:
            minDist = square
            minColor = color[0]
    return minColor, minDist


def listSort(lst):
    out = []
    for i in range(len(lst)):
        lowest = 1350
        outElement = None
        for element in lst:
            if element[1] < lowest:
                lowest = element[1]
                outElement = element
        out.append(outElement)
        lst.remove(outElement)
    return out


def main():
    argParser = argparse.ArgumentParser()
    argParser.add_argument("-i", "--input", required=True, help="path to folder containing photos")
    args = vars(argParser.parse_args())
    command = " "
    inputFolder = args["input"]
    extensions = (".jpg")
    for subdir, dirs, files in os.walk(inputFolder):
        for filename in files:
            ext = os.path.splitext(filename)[-1].lower()
            if ext in extensions:
                image = cv2.imread(os.path.join(subdir, filename))
                greyImage = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
                blurImage = cv2.GaussianBlur(greyImage, (5, 5), 0)
                thresholdImage = cv2.threshold(blurImage, 60, 255, cv2.THRESH_BINARY)[1]
                contours = cv2.findContours(thresholdImage.copy(), cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
                if imutils.is_cv2():
                    contours = contours[0]
                else:
                    contours = contours[1]
                command += "-"
                top = []
                middle = []
                bottom = []
                for contour in contours:
                    moment = cv2.moments(contour)
                    objColor, objDist = color(image, contour)
                    if objColor == "Black":
                        continue
                    if moment["m00"] >= 15000:
                        cX = int(moment["m10"]/moment["m00"])
                        cY = int(moment["m01"]/moment["m00"])
                    else:
                        continue
                    conTuple = (objColor, cX, cY)
                    if cY <= 275:
                        top.append(conTuple)
                    elif cY >= 550:
                        bottom.append(conTuple)
                    else:
                        middle.append(conTuple)
                    cv2.drawContours(image, [contour], -1, (255,255,255))
                    cv2.circle(image, (cX, cY), 7, (0, 0, 0), -1)
                    cv2.putText(image, str(objColor), (cX-10, cY-10), cv2.FONT_HERSHEY_SIMPLEX, 1, (0,0,0), 2)
                    cv2.imshow("Image", image)
                    cv2.waitKey(0)
                top = listSort(top)
                middle = listSort(middle)
                bottom = listSort(bottom)   
                command += middle[1][0][0]
                for i in range(3):
                    if i == 0:
                        command += top[0][0][0].lower() + top[1][0][0].lower() + top[2][0][0].lower()
                    elif i == 1:
                        command += middle[0][0][0].lower() + middle[1][0][0].lower() + middle[2][0][0].lower()
                    else:
                        command += bottom[0][0][0].lower() + bottom[1][0][0].lower() + bottom[2][0][0].lower()
                cv2.imshow("Image", image)
                cv2.waitKey(0)
                command += " "
    print(command)
    os.system("./solver " + command)
main()
