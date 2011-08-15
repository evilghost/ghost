
#ifndef CLONEABLE_H
#define CLONEABLE_H

namespace ghost{

	namespace utility{

		class Cloneable{
		public:
			Cloneable(){}
			virtual ~Cloneable(){}

		public:
			virtual Cloneable* Clone() = 0;
		};

	} // namespace utility

} // namespace ghost

#endif // CLONEABLE_H