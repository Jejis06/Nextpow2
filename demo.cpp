#include <climits>
#include <iostream>
#include <bitset>



/*
		undefined, 		x < 0
flp2(x) = {	0,	   		x = 0
		2^floor(log2(x)), 	x > 0

		undefined, 		x < 0
clp2(x) = {	0,	   		x = 0
		2^ceil(log2(x)), 	x > 0


   
*/

template<typename T>
T bitop(T x, short n){
	std::cout << "\n";	
	std::cout << "  \t" << std::bitset<32>(x) << '\n'; 
	std::cout << "| \t" << std::bitset<32>(x >> n) << "\n  \t"; 
	for(int i=0; i<32; i++) std::cout << "_";
	std::cout << '\n';
	std::cout << " \t" << std::bitset<32>(x | (x >> n)) << '\n'; 
	return x | (x >> n);
}

uint32_t vflp2(uint32_t x){
	x = bitop(x,1);
	x = bitop(x,2);
	x = bitop(x,4);
	x = bitop(x,8);
	x = bitop(x,16);
	std::cout << std::bitset<32>(x ^ (x >> 1)) << '\n'; 
	return x ^ (x >> 1);
}

int vclp2(uint32_t x){
	x--;  
	x = bitop(x,1);
	x = bitop(x,2);
	x = bitop(x,4);
	x = bitop(x,8);
	x = bitop(x,16);
	std::cout << std::bitset<32>(++x) << '\n'; 
	return x ;

}

int nearestLowerp2(unsigned int x){
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	
	return x ^ (x >> 1);
}
int nearestUpperp2(unsigned int x){
	x--;
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	return x+1;
}



int main(){
	uint64_t x;
	std::cin >> x;
	std::cout << vflp2(x) << '\n';
	std::cout << vclp2(x) << '\n';
}
