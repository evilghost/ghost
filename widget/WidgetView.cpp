
#include "WidgetView.h"
#include "WidgetContainer.h"

namespace ghost{

	namespace widget{

		View::View()
			: m_pContainer(0)
		{
		}

		View::~View()
		{
			DisassociateFromAll();
		}

		View* View::Clone()
		{
			return 0;
		}

		template<>
		View* View::Clone<View::WITH_CHILDREN>()
		{
			View* pObj = Clone();
			if (pObj)
			{
				// ¿ËÂ¡×ÓView
			}
			return pObj;
		}

		bool View::AllowAssociatingWidth(Associateable* pObj) const
		{
			return 0 != dynamic_cast<Container*>(pObj);
		}

		void View::DisassociateFromAll()
		{
			DisassociateFrom(m_pContainer);
		}

		bool View::IsAssociatedWidth(Associateable* pObj) const
		{
			return dynamic_cast<Container*>(pObj) == m_pContainer;
		}

		void View::DoAssociateWith(Associateable* pObj)
		{
			m_pContainer = dynamic_cast<Container*>(pObj);
		}

		void View::DoDisassociateFrom(Associateable* pObj)
		{
			m_pContainer = 0;
		}

	} // namespace widget

} // namespace ghost