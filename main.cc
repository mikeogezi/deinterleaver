#include <bits/stdc++.h>

typedef std::vector<unsigned char> vec_uchar;
typedef std::vector<bool> vec_bit;

#define S 8
#define IS_MULT_OF_S(N) (N % S == 0)

vec_uchar default_stream = {
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
};

namespace utils {
	inline auto _byte_to_X_bits (unsigned char byte, int X = S) {
		vec_bit v(S);
		
		for (int i = 0; i < X; ++i) {
			v.at(i) = (byte & (1 << i)) != 0;
		}

		std::reverse(v.begin(), v.end());
		
		return v;
	}

	inline auto _X_bits_to_byte (vec_bit v, int X = S) {
		unsigned char byte = 0;
		
		for (int i = 0; i < X; ++i) {
			if (v.at(i)) {
				byte |= 1 << i;
			}
		}
		
		return byte;
	}

	inline auto print_vec_bit (vec_bit & v) {
		auto i = 1;

		std::for_each(v.begin(), v.end(), [&] (auto bit) {
			std::cout << bit << ((i++ % S == 0) ? ", " : " ");
		});
		
		std::cout << std::endl;
	}
	
	inline auto vec_uchar_to_bits (vec_uchar & vu) {
		vec_bit vbit;
		
		std::for_each(vu.begin(), vu.end(), [&] (auto c) {
			vec_bit vb = _byte_to_X_bits(c);
		
			vbit.insert(vbit.end(), vb.begin(), vb.end());
		});
		
		return vbit;
	}

	inline auto bits_to_vec_uchar (vec_bit & vb) {
		vec_uchar vu;
		auto v_siz = vb.size();
		auto it = vb.begin();

		int times = v_siz / S;
		for (int k = 0; k < times; ++k) {
			vec_bit vb_tmp(S);
			for (int i = k * S, j = 0; i < ((k + 1) * S) && j < S; ++i, ++j) {
				vb_tmp.at(j) = vb.at(i);
			}
			std::reverse(vb_tmp.begin(), vb_tmp.end());
			auto uc = utils::_X_bits_to_byte(vb_tmp);
			vu.push_back(uc);
		}

		return vu;
	}

	inline auto print_vec_bit (vec_uchar & vu) {
		vec_bit v = vec_uchar_to_bits(vu);
		
		print_vec_bit(v);
	}

	inline auto set_size_to_mult_of_X (vec_bit & v, int X = S) {
		while (v.size() % X != 0) {
			v.pop_back();
		}
	}
};

class interleaver {
public:
	static vec_uchar interleave (vec_bit & first, vec_bit & second, int k);
	static vec_uchar interleave_uchar (vec_uchar & first, vec_uchar & second, int k);
};

class deinterleaver {
public:
	static std::pair<vec_bit, vec_bit> deinterleave (vec_uchar & stream, int k) {
		if (k <= 0 || k >= 8) {
			throw std::runtime_error("k should be between 1 and 7 inclusive");
		}

		vec_bit first;
		vec_bit second;
		
		std::for_each(stream.rbegin(), stream.rend(), [&] (unsigned char & byte) {
			vec_bit _first(S - k);
			vec_bit _second(k);
			
			vec_bit bits = utils::_byte_to_X_bits(byte);
			
			int i;
			int j;

			// utils::print_vec_bit(bits);
			
			for (i = 0; i < (S - k); ++i) {
				// std::cout << i << " " << i << " " << bits.at(i) << std::endl;
				_first.at(i) = bits.at(i);
			}
			
			for (j = 0; i < S && j < k; ++i, ++j) {
				// std::cout << j << " " << i << " " << bits.at(i) << std::endl;
				_second.at(j) = bits.at(i);
			}
			
			first.insert(first.begin(), _first.begin(), _first.end());
			second.insert(second.begin(), _second.begin(), _second.end());
		});
		
		utils::set_size_to_mult_of_X(first);
		utils::set_size_to_mult_of_X(second);

		// std::cout << "First: " << first.size() << "\n";
		// std::cout << "Second: " << second.size() << "\n";

		return {first, second};
	}
	
	static std::pair<vec_uchar, vec_uchar> deinterleave_uchar (vec_uchar & stream, int k) {
		vec_bit _first, _second;
		
		std::tie(_first, _second) = deinterleave(stream, k);
		
		vec_uchar first = utils::bits_to_vec_uchar(_first);
		vec_uchar second = utils::bits_to_vec_uchar(_second);
		
		return {first, second};
	}
};

int main(int argc, char ** argv) {
	int k = 3;
	if (argc >= 2) {
		k = atoi(argv[1]);
	}

	std::cout << "Using k as " << k << '\n';
	utils::print_vec_bit(default_stream);

	vec_bit first, second;
	std::tie(first, second) = deinterleaver::deinterleave(default_stream, k);
	
	vec_uchar _first, _second;
	std::tie(_first, _second) = deinterleaver::deinterleave_uchar(default_stream, k);

	std::cout << "First\n";
	utils::print_vec_bit(first);
	
	std::cout << "F\n";
	utils::print_vec_bit(_first);
	
	std::cout << "Second\n";
	utils::print_vec_bit(second);

	std::cout << "S\n";
	utils::print_vec_bit(_second);
	
	return EXIT_SUCCESS;
}

