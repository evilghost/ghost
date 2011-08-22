
#include "WViewAssociateChildrenProxy.h"
#include <algorithm>
#include <functional>
#include <cassert>

namespace ghost{

	namespace widget{

		namespace view_proxy{

			AssociateChildren::AssociateChildren(View& view)
				: AssociateableProxy(view)
				, m_pChildren(0)
			{

			}

			AssociateChildren::~AssociateChildren()
			{
				DisassociateFromAll();
				delete m_pChildren;
			}

			bool AssociateChildren::AllowAssociatingWidth(Associateable* pObj) const
			{
				return 0 != dynamic_cast<view_proxy::AssociateParent*>(pObj);
			}
			void AssociateChildren::DisassociateFromAll()
			{
				if (m_pChildren)
				{
					auto children(std::move(*m_pChildren));
					std::for_each(children.begin(), children.end(), 
						std::bind(std::mem_fn(&AssociateChildren::DisassociateFrom), this, std::placeholders::_1));
				}
			}

			bool AssociateChildren::IsAssociatedWidth(Associateable* pObj) const
			{
				if (m_pChildren)
				{
					view_proxy::AssociateParent* pChild = dynamic_cast<view_proxy::AssociateParent*>(pObj);
					if (pChild)
					{
						return m_pChildren->end() != std::find(m_pChildren->begin(), m_pChildren->end(), pChild);
					}
				}
				return false;
			}
			void AssociateChildren::DoAssociateWith(Associateable* pObj)
			{
				if (!m_pChildren)
				{
					m_pChildren = new ChildrenContainer;
				}
				m_pChildren->push_back(dynamic_cast<view_proxy::AssociateParent*>(pObj));
				// 对子View进行必要的初始化
			}
			void AssociateChildren::DoDisassociateFrom(Associateable* pObj)
			{
				assert(m_pChildren);
				m_pChildren->erase(std::find(m_pChildren->begin(), m_pChildren->end(), dynamic_cast<view_proxy::AssociateParent*>(pObj)));
				if (m_pChildren->empty())
				{
					delete m_pChildren;
					m_pChildren = 0;
				}
			}

		} // namespace view_proxy

	} // namespace widget

} // namespace ghost