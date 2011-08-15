
#ifndef WIDGET_CONTAINER_H
#define WIDGET_CONTAINER_H

#include "../utility/Utility.h"

namespace ghost{

	namespace widget{

		class View;

		/**
		* widget����������widgetϵͳ��ƽ̨GUIϵͳ
		* ����ά��һ��Ψһ��View����ƽ̨�������¼���ͨ�������ɷ�����View��
		* ������C++�﷨�ϵĿ�����������ͨ��Clone�ӿڽ��п�¡����ֻ��¡��������Ҳ����ͬView��һͬ��¡��
		* ��¡���ܿ�¡������ƽ̨GUI֮��Ĺ��������Խ���ʧ��ƽ̨GUI��ص�һЩ״̬������
		*/
		class Container 
			: utility::NoCopyable
			, public utility::Cloneable
			, public utility::Associateable{
		protected:
			View* m_pRootView;

		public:
			Container();

		protected:
			virtual ~Container();

		public: // ʵ��Clonable
			virtual Container* Clone();
			enum CloneParam{
				WITH_VIEWS
			};
			template<CloneParam p>
			Container* Clone();

		public: // ʵ��Associateable
			virtual bool AllowAssociatingWidth(Associateable* pObj) const;
			virtual void DisassociateFromAll();

		private: // ʵ��Associateable
			virtual bool IsAssociatedWidth(Associateable* pObj) const;
			virtual void DoAssociateWith(Associateable* pObj);
			virtual void DoDisassociateFrom(Associateable* pObj);

		public:
			bool SetRootView(View* pView);
			View* GetRootView() const
			{
				return m_pRootView;
			}

		public:
			virtual bool Invalidate(bool immediately = false) = 0;
			virtual bool Invalidate(Rect rect, bool immediately = false) = 0;
		};

	} // namespace widget

} // namespace ghost

#endif // WIDGET_CONTAINER_H