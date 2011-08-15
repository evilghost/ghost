
#ifndef ASSOCIATEABLE_H
#define ASSOCIATEABLE_H

namespace ghost{

	namespace utility{

		class Associateable{
		public:
			Associateable(){}
			virtual ~Associateable(){}

		public:
			bool AssociateWith(Associateable* pObj);
			bool DisassociateFrom(Associateable* pObj);

		public:
			virtual bool AllowAssociatingWidth(Associateable* pObj) const
			{
				return true;
			}
			virtual void DisassociateFromAll() = 0;

		private:
			virtual bool IsAssociatedWidth(Associateable* pObj) const = 0;
			virtual void DoAssociateWith(Associateable* pObj) = 0;
			virtual void DoDisassociateFrom(Associateable* pObj) = 0;
		};

	} // namespace utility

} // namespace ghost

#endif // ASSOCIATEABLE_H