
#ifndef WIDGET_VIEW_H
#define WIDGET_VIEW_H

#include "../utility/Utility.h"


namespace ghost{

	namespace widget{

		class Container;
		namespace view_proxy{
			class AssociateContainer;
			class AssociateParent;
			class AssociateChildren;
		} // namespace view_proxy

		/**
		* widget��ͼ��ÿ��widget����ĸ�����
		* ÿ��View����һ������View�����ɷ��¼�����View����View��
		* ������C++�﷨�ϵĿ�����������ͨ��Clone�ӿڽ��п�¡����ֻ��¡View����Ҳ����ͬ��View��һͬ��¡��
		* ��¡���ܿ�¡View��ƽ̨GUI֮��Ĺ��������Խ���ʧ��ƽ̨GUI��ص�һЩ״̬������
		* ͬʱ���ᶪʧ�丸view��Container��ص�һЩ״̬������
		*/
		class View 
			: private utility::NoCopyable
			, public utility::Cloneable{
		protected:
			view_proxy::AssociateContainer* m_pAssociateContainer;
			view_proxy::AssociateParent* m_pAssociateParent;
			view_proxy::AssociateChildren* m_pAssociateChildren;

		public:
			View();
			virtual ~View();

		public: // ʵ��Clonable
			virtual View* Clone();
			enum CloneParam{
				WITH_CHILDREN
			};
			template<CloneParam p>
			View* Clone();

		public: // ��ȡ�������
			view_proxy::AssociateContainer* GetAssociateContainerProxy()
			{
				return m_pAssociateContainer;
			}
			view_proxy::AssociateParent* GetAssociateParentProxy()
			{
				return m_pAssociateParent;
			}
			view_proxy::AssociateChildren* GetAssociateChildrenProxy()
			{
				return m_pAssociateChildren;
			}

		public:
			bool SetContainer(Container* pContainer);
			Container* GetContainer() const;

			bool SetParent(View* pParent);
			View* GetParent() const;
		};

	} // namespace widget

} // namespace ghost

#endif // WIDGET_VIEW_H