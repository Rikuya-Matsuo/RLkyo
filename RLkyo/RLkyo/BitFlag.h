#pragma once
#include <cstdint>
#include <cstdarg>
#include <climits>

// �e���v���[�g�֐��̎����̓w�b�_���ł��Ȃ���΂Ȃ�Ȃ��炵���̂�
// ��ނ𓾂��w�b�_�Ɏ������܂��E�E�E�B

template <typename Type>
class BitFlag final
{
public:
	BitFlag();
	~BitFlag();

	template <typename RhsType>
	Type operator=(const BitFlag<RhsType> & rhs);

	bool Get(uint8_t index) const;

	void Set(uint8_t index, bool value);

	template <typename... Arg>
	void SetInBulk(bool value, Arg... args);

	Type GetValue() const { return mFlags; }

	Type GetMask(uint8_t index) const { return 1 << index; }

	friend class BitFlag;

private:
	//uint8_t GetMaxIndex() const;

	Type mFlags;
};

template <typename Type>
BitFlag<Type>::BitFlag() :
	mFlags(0)
{

}

template <typename Type>
BitFlag<Type>::~BitFlag()
{
}

template<typename Type>
bool BitFlag<Type>::Get(uint8_t index) const
{
	return mFlags & GetMask(index);
}

template<typename Type>
void BitFlag<Type>::Set(uint8_t index, bool value)
{
	value ?
		mFlags |= GetMask(index) :
		mFlags &= ~GetMask(index);
}

/*
template<typename Type>
inline uint8_t BitFlag<Type>::GetMaxIndex() const
{
	// �������̃p�f�B���O�i�l�ߕ��j�̉e���Ő������l���Ԃ��Ă��Ȃ����Ƃ�����炵���̂ŉ��̏�������f�O�B
	// return sizeof(Type) * CHAR_BIT;

	uint8_t bit = 0;

	Type num = 0;
	Type prevNum;

	// ���[�v�񐔂�ߖ񂷂邽�߂ɁA�o�C�g�P�ʂŃ��[�v����
	do
	{
		// �v�Z�O�̒l���L�^
		prevNum = num;

		// �����珇��1�o�C�g���A�r�b�g��S�ė��Ă�
		num |= static_cast<Type>(UINT8_MAX) << bit;

		// ��̌v�Z�ŉ��r�b�g�V�t�g�����邩�B
		bit += CHAR_BIT;

		// �r�b�g�P��or���Z�q�̏����̌�A�v�Z�O�ƒl���ς���Ă��Ȃ� == num�̃r�b�g�͂��ׂė����Ă���
		// ����āA�v�Z�O�ƕς���Ă���ꍇ�̓��[�v���p������B
	} while (num != prevNum);

	// ���[�v���ōs���߂�������߂���return
	return (bit -= CHAR_BIT);
}
*/

template<typename Type>
template<typename RhsType>
Type BitFlag<Type>::operator=(const BitFlag<RhsType>& rhs)
{
	// rhs�̃t���O���擾
	RhsType rhsFlags = rhs.mFlags;

	// rhsFlags�����̒l���������̏���
	Type mask = 0;
	if (rhsFlags < 0)
	{
		// rhsFlags�̈�ԏ�̃r�b�g�i�����r�b�g�j���}�X�N�Ƃ��Đݒ�
		mask |= 1 << (rhs.GetMaxIndex() - 1);

		// ��ԏ�̃r�b�g���O��
		rhsFlags &= ~static_cast<RhsType>(mask);
	}

	mFlags = static_cast<Type>(rhsFlags);
	mFlags |= mask;

	return mFlags;
}


template<typename Type>
template<typename ...Arg>
void BitFlag<Type>::SetInBulk(bool value, Arg ...indexes)
{
	int indexArray[] = { indexes... };

	const size_t indexMass = sizeof...(indexes);

	for (size_t i = 0; i < indexMass; ++i)
	{
		// �I�[�o�[�t���[�Ō�쓮���N�����Ȃ��悤�ɁAuint8_t�̃T�C�Y�Ɏ��܂邩���m�F
		if (indexArray[i] > UINT8_MAX)
		{
			continue;
		}
		uint8_t index = static_cast<uint8_t>(indexArray[i]);
		Set(index, value);
	}
}