//
// F# image processing functions.
//
//
// Aqsa Arif
// University of illinois at Chicago
// Fall 2022

namespace ImageLibrary

module Operations =
  //
  // all functions must be indented
  //

  //
  // Grayscale:
  //
  // Converts the image into grayscale and returns the 
  // resulting image as a list of lists. Pixels in grayscale
  // have the same value for each of the Red, Green and Blue
  // values in the RGB value.  Conversion to grayscale is done
  // by using a WEIGHTED AVERAGE calculation.  A normal average
  // (adding the three values and dividing by 3) is not the best,
  // since the human eye does not perceive the brightness of 
  // red, green and blue the same.  The human eye perceives 
  // green as brighter than red and it perceived red as brighter
  // than blue.  Research has shown that the following weighted
  // values should be used when calculating grayscale.
  //  - the green value should account for 58.7% of the grayscale.
  //  - the red value should account for   29.9% of the grayscale.
  //  - the blue value should account for  11.4% of the grayscale.
  //
  // So if the RGB values were (25, 75, 250), the grayscale amount 
  // would be 80, (25 * 0.299 + 75 * 0.587 + 250 * 0.114 => 80)
  // and then all three RGB values would become 80 or (80, 80, 80).
  // We will use truncation to cast from the floating point result 
  // to the integer grayscale value.
  //
  // Returns: updated image.
  //

  // helper function for greyscale
  let graymath (a:int) (b:int) (c:int) = 
    let num = int(float(a) * 0.299 + float(b) * 0.587 + float(c) * 0.114)
    (num,num,num)

  // Helper function to access tuple values
  let math (image:(int*int*int) list list) =
    image |> List.map (fun container -> 
    container |> List.map (fun (r,g,b) -> graymath(r)(g)(b)))
    
  // returns image header information for debugging
  let imageStats (width:int) (height:int) (depth:int) =
    printfn "Width of image is %d" width
    printfn "Height of image is %d" height
    printfn "Color saturation max is %d" depth

  let rec Grayscale (width:int) 
                    (height:int) 
                    (depth:int) 
                    (image:(int*int*int) list list) = 
    imageStats(width)(height)(depth)
    math(image)
    
  
  //
  // Threshold
  //
  // Thresholding increases image separation --- dark values 
  // become darker and light values become lighter. Given a 
  // threshold value in the range 0 < threshold < color depth,
  // each RGB value is compared to see if it's > threshold.
  // If so, that RGB value is replaced by the color depth;
  // if not, that RGB value is replaced with 0. 
  //
  // Example: if threshold is 100 and depth is 255, then given 
  // a pixel (80, 120, 160), the new pixel is (0, 255, 255).
  //
  // Returns: updated image.
  //
  //  returns image header information for debugging for Threshold
  let imageStatsT (width:int) (height:int) (depth:int) (thresh:int) =
    printfn "Width of image is %d" width
    printfn "Height of image is %d" height
    printfn "Color saturation max is %d" depth
    printfn "Threshhold is %d" thresh

  // Threshold helper function 
  let threshmath (a:int) (b:int) (c:int) (t:int) (d:int) = 
    let numA = if a<=t then 0  else d
    let numB = if b<=t then 0  else d
    let numC = if c<=t then 0  else d
    (numA,numB,numC)

  let rec Threshold (width:int) 
                    (height:int)
                    (depth:int)
                    (image:(int*int*int) list list)
                    (threshold:int) = 
    imageStatsT(width)(height)(depth)(threshold)
    // reduce list to the tuples and use helper function to apply 
    // threshold math
    image |> List.map (fun container -> 
    container |> List.map (fun (r,g,b) -> 
    threshmath(r)(g)(b)(threshold)(depth)))
  //
  // FlipHorizontal:
  //
  // Flips an image so that what’s on the left is now on 
  // the right, and what’s on the right is now on the left. 
  // That is, the pixel that is on the far left end of the
  // row ends up on the far right of the row, and the pixel
  // on the far right ends up on the far left. This is 
  // repeated as you move inwards toward the row's center.
  //
  // Returns: updated image.
  //
  let rec FlipHorizontal (width:int)
                         (height:int)
                         (depth:int)
                         (image:(int*int*int) list list) = 
    
    imageStats(width)(height)(depth)
    // get rows and reverse list
    image |> List.map (fun container -> 
    container |> List.rev)
  //
  // Edge Detection:
  //
  // Edge detection is an algorithm used in computer vision to help
  // distinguish different objects in a picture or to distinguish an
  // object in the foreground of the picture from the background.
  //
  // Edge Detection replaces each pixel in the original image with
  // a black pixel, (0, 0, 0), if the original pixel contains an 
  // "edge" in the original image.  If the original pixel does not
  // contain an edge, the pixel is replaced with a white pixel 
  // (255, 255, 255).
  //
  // An edge occurs when the color of pixel is "signigicantly different"
  // when compared to the color of two of its neighboring pixels. 
  // We only compares each pixel in the image with the 
  // pixel immediately to the right of it and with the pixel
  // immediately below it. If either pixel has a color difference
  // greater than a given threshold, then it is "significantly
  // different" and an edge occurs. Note that the right-most column
  // of pixels and the bottom-most column of pixels can not perform
  // this calculation so the final image contain one less column
  // and one less row than the original image.
  //
  // To calculate the "color difference" between two pixels, we
  // treat the each pixel as a point on a 3-dimensional grid and
  // we calculate the distance between the two points using the
  // 3-dimensional extension to the Pythagorean Theorem.
  // Distance between (x1, y1, z1) and (x2, y2, z2) is
  //  sqrt ( (x1-x2)^2 + (y1-y2)^2 + (z1-z2)^2 )
  //
  // The threshold amount will need to be given, which is an 
  // integer 0 < threshold < 255.  If the color distance between
  // the original pixel either of the two neighboring pixels 
  // is greater than the threshold amount, an edge occurs and 
  // a black pixel is put in the resulting image at the location
  // of the original pixel. 
  //
  // Returns: updated image.
  //
  let rec EdgeDetect (width:int)
               (height:int)
               (depth:int)
               (image:(int*int*int) list list)
               (threshold:int) = 
    image
    //image |> List.mapi (fun i x -> printfn "%A %A x" i x)

    //image |> List.mapi (fun i x -> helper2(i)(x)(width)(height))

    //image |> List.map (fun container -> 
    //container |> List.mapi (fun i x -> helper(i)(x)))
    
    // printfn "%A %A x" i x
    //let list2 = image |> List.transpose |> 
    //  List.map (fun container -> rowHelper(container))


  //
  // RotateRight90:
  //
  // Rotates the image to the right 90 degrees.
  //
  // Returns: updated image.
  //
  let rec RotateRight90 (width:int)
                        (height:int)
                        (depth:int)
                        (image:(int*int*int) list list) = 

    imageStats(width)(height)(depth)
    // convert rows to columns and columns to rows and reverse
    image |> List.transpose |> List.map (fun container -> 
    container |> List.rev)

