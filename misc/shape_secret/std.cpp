#include "bitmap_image.hpp"

#include <fstream>
#include <vector>
#include <sstream>

using byte = unsigned char;

class shape_file
{
public:
	shape_file(std::string filepath) noexcept
	{
		std::ifstream fin;
		fin.open(filepath, fin.in | fin.binary);
		if (fin.is_open())
		{
			auto sz = static_cast<size_t>(fin.seekg(0, fin.end).tellg());
			fin.seekg(0, fin.beg);
			m_data.resize(sz);
			fin.read(reinterpret_cast<char*>(m_data.data()), sz);
			fin.close();
		}
	}

	uint16_t get_width() const
	{
		return at<uint16_t>(2);
	}

	uint16_t get_height() const
	{
		return at<uint16_t>(4);
	}

	uint16_t get_framecount() const
	{
		return at<uint16_t>(6);
	}

	struct frame_header
	{
		uint16_t X;
		uint16_t Y;
		uint16_t Width;
		uint16_t Height;
		uint8_t Flags;
		// char padding[3]
		uint32_t Color;
		uint32_t unused;
		uint32_t Offset;
	};
	static_assert(sizeof(frame_header) == 24);

	frame_header& get_frameheader(size_t idx) const
	{
		return at<frame_header>(8 + sizeof(frame_header) * idx);
	}

	std::vector<byte> get_framedata(size_t idx)
	{
		std::vector<byte> ret;

		const auto& header = get_frameheader(idx); 

		size_t pixel_count = header.Width * header.Height;
		ret.resize(pixel_count);

		if (header.Flags & 2)
		{
			size_t pos = 0;
			byte* ptr = &at<byte>(header.Offset);
			for (int j = 0; j < header.Height; ++j)
			{
				size_t len = (ptr[0] | (ptr[1] << 8));
				for (size_t k = 2; k < len; ++k)
				{
					byte b = ptr[k];
					if(b == 0)
					{
						byte cnt = ptr[++k];
						memset(&ret[pos], cnt, 0);
						pos += cnt;
					}
					else
						ret[pos++] = b;
				}
				ptr += len;
			}
		}
		else
			memcpy(&ret[0], &at<byte>(header.Offset), pixel_count);

		return ret;
	}

private:
	template<typename T>
	T& at(size_t offset) const
	{
		return *const_cast<T*>(reinterpret_cast<const T*>(m_data.data() + offset));
	}

	std::vector<byte> m_data;
};

int main()
{
	shape_file shp("./shape_secret.shp");

	bitmap_image bmp;
	bmp.setwidth_height(shp.get_framecount() * shp.get_width(), shp.get_height());

	for (size_t i = 0; i < shp.get_framecount(); ++i)
	{
		const auto& header = shp.get_frameheader(i);
		auto data = shp.get_framedata(i);

		size_t cnt = 0;
		for (size_t y = header.Y; y < header.Y + header.Height; ++y)
		{
			for (size_t x = header.X; x < header.X + header.Width; ++x)
			{
				if (data[cnt])
				{
					bmp.set_pixel(i * shp.get_width() + x, y, 255, 0, 0);
				}
				++cnt;
			}
		}
	}
	bmp.save_image("output.bmp");
}