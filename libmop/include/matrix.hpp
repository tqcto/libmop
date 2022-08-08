#pragma once
#include "deflate/define.h"
#include "deflate/deflate.hpp"

namespace mop {

	class matrix {

	private:

		//BITMAPDATA_t	bmp;
		//uchar*			_data = nullptr;

		// ����
		uint _w = 0;
		// �c��
		uint _h = 0;
		// �F�f��
		uint _c = 0;
		// ��̂Ƃ��^
		bool _empty = 0;

	public:

		// �摜�f�[�^
		uchar* data = nullptr;

	public:

		/**
		* @fn
		* @brief ��̃N���X���쐬����R���X�g���N�^�ł��B������g�p�����ꍇ���������m�ۂ���Ȃ��̂ŁAdata_malloc �֐��𗘗p����Ȃǂ��ă��������m�ۂ���K�v������܂��B
		*/
		DLL_EXPORT matrix(void) noexcept : _empty(1) {};
		/**
		* @fn
		* @brief �摜�t�@�C����ǂݍ��݂܂��B
		* @param filename �摜�t�@�C���p�X
		*/
		DLL_EXPORT matrix(const char* filename);
		/**
		* @fn
		* @brief �����̉摜�N���X���R�s�[���܂��B
		* @param src �摜�N���X�̃|�C���^
		*/
		DLL_EXPORT matrix(matrix* src);
		/**
		* @fn
		* @brief �T�C�Y���w�肵�ĉ摜�f�[�^���쐬���܂��B
		* @param width �s��
		* @param height ��
		* @param channels �F�f��
		*/
		DLL_EXPORT matrix(int width, int height, int channels);

		/**
		* @fn
		* @brief �f�X�g���N�^�ł��B�摜�f�[�^�̃������̉���Ȃǂ��s���܂��B
		*/
		DLL_EXPORT ~matrix(void);

		#pragma region memory setup
		/**
		* @fn
		* @brief �摜�f�[�^�̃��������m�ۂ��܂��B
		* @param width �s��
		* @param height ��
		* @param channels �F�f��
		* @return ���������m�ۂł����ꍇ��0�A�ł��Ȃ������ꍇ��-1�ȉ���Ԃ��܂��B
		*/
		DLL_EXPORT int Malloc(int width, int height, int channels);
		/**
		* @fn
		* @brief �摜�f�[�^�̃�������������܂��B
		*/
		DLL_EXPORT void Free(void);
		/**
		* @fn
		* @brief �摜�f�[�^���R�s�[���܂��B
		* @param data �R�s�[����f�[�^
		* @param width �s��
		* @param height ��
		* @param channels �F�f��
		*/
		DLL_EXPORT void Memcpy(uchar* data, int width, int height, int channels);
		#pragma endregion

		/**
		* @fn
		* @brief �w�肵�����W�̉�f�f�[�^���擾���܂��B
		* @param x �s�ԍ�
		* @param y ��ԍ�
		* @param c �F�f�ԍ�
		* @return ��f�f�[�^�̃|�C���^��Ԃ��܂��B
		*/
		DLL_EXPORT uchar* access(int x, int y, int c);
		/**
		* @fn
		* @brief �w�肵�����W�̉�f�f�[�^���擾���܂��B
		* @param x �s�ԍ�
		* @param y ��ԍ�
		* @return ��f�f�[�^�̃|�C���^��Ԃ��܂��B
		*/
		DLL_EXPORT rgbp access(int x, int y);

		/**
		* @fn
		* @brief �w�肵�����W�̉�f�f�[�^��HSV�l���擾���܂��B
		* @param x �s�ԍ�
		* @param y ��ԍ�
		* @return ��f�f�[�^��HSV�l��Ԃ��܂��B
		*/
		DLL_EXPORT hsv getHSV(int x, int y);
		/**
		* @fn
		* @brief �w�肵�����W�̉�f�f�[�^��HSV�l��ύX���܂��B
		* @param x �s�ԍ�
		* @param y ��ԍ�
		* @param c HSV�l
		*/
		DLL_EXPORT void setHSV(int x, int y, hsv c);

		#pragma region matrix op
		/**
		* @fn
		* @brief �摜�f�[�^���T�C�Y�ύX���܂��B
		* @param size_w(%) �s�T�C�Y
		* @param size_h(%) ��T�C�Y
		*/
		DLL_EXPORT void Resize(double size_w, double size_h);
		/**
		* @fn
		* @brief �摜�f�[�^����]���܂��B
		* @param angle ��]�p�x
		* @param mode �O���_�̃��b�s���O�⊮���@�w��
		* @param cx �s�����̒��S��
		* @param cy ������̒��S��
		*/
		DLL_EXPORT void Rotate(double angle, repeat_mode mode = repeat_none, int cx = 0, int cy = 0);
		#pragma endregion

		#pragma region color variation
		/**
		* @fn
		* @brief �摜�f�[�^��HSV�F��Ԃɕϊ����� �F���A �ʓx�A ���x ��ύX���܂��B
		* @param h �F��
		* @param s �ʓx
		* @param v ���x
		*/
		DLL_EXPORT void HSV(int h, int s, int v);
		#pragma endregion

		/**
		* @fn
		* @brief �摜�f�[�^��ۑ����܂��B
		* @param filename �ۑ��t�@�C���p�X
		* @param quality �ۑ�����𑜓x
		* @return �ۑ������������ꍇ��0�A�ł��Ȃ������ꍇ�͂���ȊO��Ԃ��܂��B
		*/
		DLL_EXPORT int encode(const char* filename, int quality = 50);

		#pragma region getter
		/**
		* @fn
		* @brief �s�̒������擾���܂��B
		*/
		DLL_EXPORT inline int width(void) const noexcept;
		/**
		* @fn
		* @brief ��̒������擾���܂��B
		*/
		DLL_EXPORT inline int height(void) const noexcept;
		/**
		* @fn
		* @brief ��f�����擾���܂��B
		*/
		DLL_EXPORT inline int channel(void) const noexcept;
		/**
		* @fn
		* @brief �摜�f�[�^���擾���܂��B
		*/
		DLL_EXPORT inline uchar* data_(void) const noexcept;
		DLL_EXPORT inline uchar* const* data_ptr(void) const noexcept;
		/**
		* @fn
		* @brief �摜�f�[�^���󂩂ǂ������擾���܂��B
		*/
		DLL_EXPORT inline int empty(void) const noexcept;
		#pragma endregion

		#pragma region operator
		DLL_EXPORT matrix& operator = (const matrix& src);
		#pragma endregion

	};

}
