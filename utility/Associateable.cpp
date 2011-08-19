
#include "Associateable.h"

namespace ghost{

	namespace utility{

		bool Associateable::AssociateWith(Associateable* pObj)
		{
			if (!pObj)
			{
				return false;
			}
			if (this == pObj)
			{
				return false;
			}
			if (IsAssociatedWidth(pObj))
			{
				return true;
			}
			if (!AllowAssociatingWidth(pObj))
			{
				return false;
			}
			DoAssociateWith(pObj);
			if (!pObj->AssociateWith(this))
			{
				DoDisassociateFrom(pObj);
				return false;
			}
			return true;
		}
		bool Associateable::DisassociateFrom(Associateable* pObj)
		{
			if (!pObj)
			{
				return false;
			}
			if (!IsAssociatedWidth(pObj))
			{
				return true;
			}
			DoDisassociateFrom(pObj);
			if (!pObj->DisassociateFrom(this))
			{
				DoAssociateWith(pObj);
				return false;
			}
			return true;
		}

	} // namespace utility

} // namespace ghost