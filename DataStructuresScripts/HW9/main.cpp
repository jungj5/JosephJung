#include <cstdlib>
#include "image.h"
#include <cmath>
#include <map>
#include <vector>

// ===================================================================================================
// ===================================================================================================

//self_made helper function to find offset value with largest amount of pixels
std::pair<int, int>  find_max(std::map<std::pair<int, int>, std::vector<std::pair<int, int> > > &container) {
	std::map<std::pair<int, int>, std::vector<std::pair<int, int> > >::iterator iter;
	std::pair<int, int> answer;
	int size = 0;
	for (iter = container.begin(); iter != container.end(); ++iter) {
		if (iter->second.size() > size) {
			size = iter->second.size();
			answer = iter->first;

		}
	}
	return answer;
}

void Compress(const Image<Color> &input, 
              Image<bool> &occupancy, Image<Color> &hash_data, Image<Offset> &offset) {

//calculating number of colored spots (p)
	occupancy.Allocate(input.Width(), input.Height()); //<---- allocate occupancy image
	int p = 0;
	for (int i = 0; i < input.Width(); ++i) {
		for (int j = 0; j < input.Height(); ++j) {
			if (input.GetPixel(i, j).isWhite() == false) {
				p += 1;
				//set true on the corresponding occupany spot if it is not white.
				occupancy.SetPixel(i, j, true);
			}
		}
	}
//finding hash/offset sizes

	int s_offset = ceil(sqrt(p / 4));
	int s_hash = ceil(sqrt(1.01 * p));
	if (s_hash % s_offset != 0) {
		s_hash += 1;
	}

	//Allocating the images 
	offset.Allocate(s_offset, s_offset);
	hash_data.Allocate(s_hash, s_hash);
	
	std::map<std::pair<int, int>, std::vector<std::pair<int, int> > > container;
	//Going through the input image.
	for (int i = 0; i < input.Width(); ++i) {
		for (int j = 0; j < input.Height(); ++j) {
			//If the spot is not white..
			if (input.GetPixel(i, j).isWhite() == false) {
				std::pair<int, int> tmp1(i % s_offset, j % s_offset);
				std::pair<int, int> tmp2(i, j);
				container[tmp1].push_back(tmp2);


				//Color tmp = input.GetPixel(i, j);
				//offset.SetPixel(i%s_offset, j%s_offset, tmp);
			}
		}
	}
	std::map<std::pair<int, int>, std::vector<std::pair<int, int> > >::iterator iter1;

	int dx;
	int dy;
	std::map<std::pair<int, int>, std::vector<std::pair<int, int> > > just_in_case = container;
	LOOP:while (container.size() > 0) {
		dx = 0;
		dy = 0;
		std::pair<int, int> max_offset = find_max(container);
		for (int i = 0; i < container[max_offset].size(); ++i) {
			//i, j positions of the pixel
			int x = container[max_offset][i].first;
			int y = container[max_offset][i].second;

			//hd = hashdata

			bool found_spot = false;
			while (found_spot == false) {
				int hd_x = (x + dx) % s_hash;
				int hd_y = (y + dy) % s_hash;
				
				if (hash_data.GetPixel(hd_x, hd_y).isWhite() == true) {
					hash_data.SetPixel(hd_x, hd_y, input.GetPixel(x, y));
					found_spot = true;
				}
				else if (dx < 15) {
					dx += 1;
		
				}
				else if (dy < 15){
					dy += 1;
				}
				else {
					s_hash += 1;
					hash_data.Allocate(s_hash, s_hash);
					offset.Allocate(s_offset, s_offset);
					dx = 0;
					dy = 0;
					container = just_in_case;
					goto LOOP;
				}

			}
			if (found_spot == true) {
				Offset tmp_offset = Offset(dx, dy);
				offset.SetPixel(x % s_offset, y % s_offset, tmp_offset);
			}
		}
		container.erase(max_offset);
	}

}


void UnCompress(const Image<bool> &occupancy, const Image<Color> &hash_data, const Image<Offset> &offset, 
                Image<Color> &output) {

	int offset_size = offset.Width();
	int hash_size = hash_data.Width();
	output.Allocate(occupancy.Width(), occupancy.Height());
//going through the occupancy
	for (int i = 0; i < occupancy.Width(); ++i) {
		for (int j = 0; j < occupancy.Height(); ++j) {
			//if it is not white...
			if (occupancy.GetPixel(i, j) == true) {
				Offset tmp = offset.GetPixel(i % offset_size, j % offset_size);
				Color hash = hash_data.GetPixel((i+tmp.dx)%hash_size, (j + tmp.dy)%hash_size);
				output.SetPixel(i, j, hash);
			}
		}
	}


	

}


// ===================================================================================================
// ===================================================================================================

// Takes in two 24-bit color images as input and creates a b&w output
// image (black where images are the same, white where different)
void Compare(const Image<Color> &input1, const Image<Color> &input2, Image<bool> &output) {

  // confirm that the files are the same size
  if (input1.Width() != input2.Width() ||
      input1.Height() != input2.Height()) {
    std::cerr << "Error: can't compare images of different dimensions: " 
         << input1.Width() << "x" << input1.Height() << " vs " 
         << input2.Width() << "x" << input2.Height() << std::endl;
  } else {
    // make sure that the output images is the right size to store the
    // pixel by pixel differences
    output.Allocate(input1.Width(),input1.Height());
    int count = 0;
    for (int i = 0; i < input1.Width(); i++) {
      for (int j = 0; j < input1.Height(); j++) {
        Color c1 = input1.GetPixel(i,j);
        Color c2 = input2.GetPixel(i,j);
        if (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b)
          output.SetPixel(i,j,true);
        else {
          count++;
          output.SetPixel(i,j,false);
        }
      }      
    }     

    // confirm that the files are the same size
    if (count == 0) {
      std::cout << "The images are identical." << std::endl;
    } else {
      std::cout << "The images differ at " << count << " pixel(s)." << std::endl;
    }
  }
}

// ===================================================================================================
// ===================================================================================================

// to allow visualization of the custom offset image format
void ConvertOffsetToColor(const Image<Offset> &input, Image<Color> &output) {
  // prepare the output image to be the same size as the input image
  output.Allocate(input.Width(),input.Height());
  for (int i = 0; i < output.Width(); i++) {
    for (int j = 0; j < output.Height(); j++) {
      // grab the offset value for this pixel in the image
      Offset off = input.GetPixel(i,j);
      // set the pixel in the output image
      int dx = off.dx;
      int dy = off.dy;
      assert (dx >= 0 && dx <= 15);
      assert (dy >= 0 && dy <= 15);
      // to make a pretty image with purple, cyan, blue, & white pixels:
      int red = dx * 16;
      int green = dy *= 16;
      int blue = 255;
      assert (red >= 0 && red <= 255);
      assert (green >= 0 && green <= 255);
      output.SetPixel(i,j,Color(red,green,blue));
    }
  }
}

// ===================================================================================================
// ===================================================================================================

void usage(char* executable) {
  std::cerr << "Usage:  4 options" << std::endl;
  std::cerr << "  1)  " << executable << " compress input.ppm occupancy.pbm data.ppm offset.offset" << std::endl;
  std::cerr << "  2)  " << executable << " uncompress occupancy.pbm data.ppm offset.offset output.ppm" << std::endl;
  std::cerr << "  3)  " << executable << " compare input1.ppm input2.ppm output.pbm" << std::endl;
  std::cerr << "  4)  " << executable << " visualize_offset input.offset output.ppm" << std::endl;
}



// ===================================================================================================
// ===================================================================================================

int main(int argc, char* argv[]) {
  if (argc < 2) { usage(argv[1]); exit(1); }

  if (argv[1] == std::string("compress")) {
    if (argc != 6) { usage(argv[1]); exit(1); }
    // the original image:
    Image<Color> input;
    // 3 files form the compressed representation:
    Image<bool> occupancy;
    Image<Color> hash_data;
    Image<Offset> offset;
    input.Load(argv[2]);
    Compress(input,occupancy,hash_data,offset);
    // save the compressed representation
    occupancy.Save(argv[3]);
    hash_data.Save(argv[4]);
    offset.Save(argv[5]);

  } else if (argv[1] == std::string("uncompress")) {
    if (argc != 6) { usage(argv[1]); exit(1); }
    // the compressed representation:
    Image<bool> occupancy;
    Image<Color> hash_data;
    Image<Offset> offset;
    occupancy.Load(argv[2]);
    hash_data.Load(argv[3]);
    offset.Load(argv[4]);
    // the reconstructed image
    Image<Color> output;
    UnCompress(occupancy,hash_data,offset,output);
    // save the reconstruction
    output.Save(argv[5]);
  
  } else if (argv[1] == std::string("compare")) {
    if (argc != 5) { usage(argv[1]); exit(1); }
    // the original images
    Image<Color> input1;
    Image<Color> input2;    
    input1.Load(argv[2]);
    input2.Load(argv[3]);
    // the difference image
    Image<bool> output;
    Compare(input1,input2,output);
    // save the difference
    output.Save(argv[4]);

  } else if (argv[1] == std::string("visualize_offset")) {
    if (argc != 4) { usage(argv[1]); exit(1); }
    // the 8-bit offset image (custom format)
    Image<Offset> input;
    input.Load(argv[2]);
    // a 24-bit color version of the image
    Image<Color> output;
    ConvertOffsetToColor(input,output);
    output.Save(argv[3]);

  } else {
    usage(argv[0]);
    exit(1);
  }
}

// ===================================================================================================
// ===================================================================================================
