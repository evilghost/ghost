
#ifndef NO_COPYABLE_H
#define NO_COPYABLE_H

namespace ghost{

	namespace utility{

		class NoCopyable{
		protected:
			NoCopyable(){}
			~NoCopyable(){}

		protected:
			NoCopyable(const NoCopyable&);
			NoCopyable& operator =(const NoCopyable&);
		};

	} // namespace utility

} // namespace ghost

#endif // NO_COPYABLE_H