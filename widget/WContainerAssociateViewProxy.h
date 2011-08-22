
#ifndef WIDGET_CONTAINER_ASSOCIATE_VIEW_PROXY_H
#define WIDGET_CONTAINER_ASSOCIATE_VIEW_PROXY_H

#include "../utility/Utility.h"
#include "WContainer.h"
#include "WViewAssociateContainerProxy.h"

namespace ghost{

	namespace widget{

		class View;

		namespace container_proxy{

			class AssociateView
				: public utility::SingleAssociateableProxy<Container, view_proxy::AssociateContainer>
			{
			public:
				explicit AssociateView(Container& container);
				virtual ~AssociateView();

			public:
				View* GetRootView() const;

			protected: //  µœ÷Associateable
				virtual void DoAssociateWith(Associateable* pObj);
			};

		} // namespace container_proxy

	} // namespace widget

} // namespace ghost

#endif // WIDGET_CONTAINER_ASSOCIATE_VIEW_PROXY_H