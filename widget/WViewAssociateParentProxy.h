
#ifndef WIDGET_CONTAINER_ASSOCIATE_PARENT_PROXY_H
#define WIDGET_CONTAINER_ASSOCIATE_PARENT_PROXY_H

#include "../utility/Utility.h"
#include "WView.h"
#include "WViewAssociateChildrenProxy.h"

namespace ghost{

	namespace widget{

		namespace view_proxy{

			class AssociateParent
				: public utility::SingleAssociateableProxy<View, AssociateChildren>
			{
			public:
				explicit AssociateParent(View& view);
				virtual ~AssociateParent();

			public:
				View* GetParent() const;

			protected: //  µœ÷Associateable
				virtual void DoDisassociateFrom(Associateable* pObj);
			};

		} // namespace view_proxy

	} // namespace widget

} // namespace ghost

#endif // WIDGET_CONTAINER_ASSOCIATE_PARENT_PROXY_H