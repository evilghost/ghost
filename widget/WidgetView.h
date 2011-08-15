
#ifndef WIDGET_VIEW_H
#define WIDGET_VIEW_H

#include "../utility/Utility.h"

namespace ghost{

	namespace widget{

		class Container;

		/**
		* widget��ͼ��ÿ��widget����ĸ�����
		* ÿ��View����һ������View�����ɷ��¼�����View����View��
		* ������C++�﷨�ϵĿ�����������ͨ��Clone�ӿڽ��п�¡����ֻ��¡View����Ҳ����ͬ��View��һͬ��¡��
		* ��¡���ܿ�¡View��ƽ̨GUI֮��Ĺ��������Խ���ʧ��ƽ̨GUI��ص�һЩ״̬������
		*/
		class View 
			: utility::NoCopyable
			, public utility::Cloneable
			, public utility::Associateable{
		protected:
			Container* m_pContainer;

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

		public: // ʵ��Associateable
			virtual bool AllowAssociatingWidth(Associateable* pObj) const;
			virtual void DisassociateFromAll();

		private: // ʵ��Associateable
			virtual bool IsAssociatedWidth(Associateable* pObj) const;
			virtual void DoAssociateWith(Associateable* pObj);
			virtual void DoDisassociateFrom(Associateable* pObj);
		};

	} // namespace widget

} // namespace ghost

#endif // WIDGET_VIEW_H