# PGMImageEditor


Digital Images are an interesting class of objects we come across frequently. Digital image processing is an active area of development and software systems and tools addressing problems in this area are always in demand. In this mini-project we are going to perform some well-defined and well-understood operations on digital images. These
operations are inspired from the features available in commonly used image viewing/processing software systems like irfanview, MS-paint … To make the life easier we will begin using ASCII pgm files as our input/output format and later we will relax this restriction and might handle other formats as well.

Some of the basic features we will offer to our user are:

FILE HANDLING
Open File (initially pgm file will be supported only)

Save File


IMAGE TRANSFORMATIONS

Rotate an Image by a certain angle (theta)

Translate an Image

Scale an image (scale up and scale down)

Rotation will be with or without clipping
Rotation will be performed either in the forward or reverse.

Flip an Image

Apply a general linear transformation using a transformation matrix

Enhance an image by applying a filter. Some pre-defined filters must be provided:
Mean Filter
Median Filter
Apply filters using filter masks with masks of varying sizes

Combining Two Images to form a new image
Combine by placing two images side-by-side
Combine by placing two images top-to-bottom
Combining Images to form a video
Combine two Images so that First image fades away and the second appears
Combine All Images present in a directory/folder so that each image appears in the image for a fixed time duration given by the user

Miscellaneous
Computing Image derivatives and negatives
Changing Image Brightness and Contrast levels
Quantize an Image
