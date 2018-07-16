import argparse
import imutils
import cv2

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-f", "--first", required=True,
	help="first input image")
ap.add_argument("-s", "--second", required=True,
	help="second input file")
ap.add_argument("-a", "--min-area", type=int, default=500000, 
	help="minimum area size")
ap.add_argument("-o", "--output", required=True, help="Output file")
args = vars(ap.parse_args())


referenceImage = cv2.imread(args["first"])
image = cv2.imread(args["second"])

gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
gray = cv2.GaussianBlur(gray, (21, 21), 0)

referenceImage = cv2.cvtColor(referenceImage, cv2.COLOR_BGR2GRAY)
referenceImage = cv2.GaussianBlur(referenceImage, (21, 21), 0)

deltaImage = cv2.absdiff(referenceImage, gray)
thresh = cv2.threshold(deltaImage, 25, 255, cv2.THRESH_BINARY)[1]

# dilate the thresholded image to fill in holes, then find contours
# on thresholded image
thresh = cv2.dilate(thresh, None, iterations=2)
cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,
    cv2.CHAIN_APPROX_SIMPLE)
cnts = cnts[0] if imutils.is_cv2() else cnts[1]

# loop over the contours
for c in cnts:
    # if the contour is too small, ignore it
    if cv2.contourArea(c) < args["min_area"]:
        continue

    # compute the bounding box for the contour, draw it on the frame,
    # and update the text
    (x, y, w, h) = cv2.boundingRect(c)
    cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)


cv2.imwrite(args["output"], image)
print("Done")
