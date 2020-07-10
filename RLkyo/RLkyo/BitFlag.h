#pragma once
#include <cstdint>
#include <cstdarg>
#include <climits>

// テンプレート関数の実装はヘッダ側でしなければならないらしいので
// やむを得ずヘッダに実装します・・・。

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
	// メモリのパディング（詰め物）の影響で正しい値が返ってこないことがあるらしいので下の書き方を断念。
	// return sizeof(Type) * CHAR_BIT;

	uint8_t bit = 0;

	Type num = 0;
	Type prevNum;

	// ループ回数を節約するために、バイト単位でループする
	do
	{
		// 計算前の値を記録
		prevNum = num;

		// 下から順に1バイトずつ、ビットを全て立てる
		num |= static_cast<Type>(UINT8_MAX) << bit;

		// 上の計算で何ビットシフトさせるか。
		bit += CHAR_BIT;

		// ビット単位or演算子の処理の後、計算前と値が変わっていない == numのビットはすべて立っていた
		// よって、計算前と変わっている場合はループを継続する。
	} while (num != prevNum);

	// ループ内で行き過ぎた分を戻してreturn
	return (bit -= CHAR_BIT);
}
*/

template<typename Type>
template<typename RhsType>
Type BitFlag<Type>::operator=(const BitFlag<RhsType>& rhs)
{
	// rhsのフラグを取得
	RhsType rhsFlags = rhs.mFlags;

	// rhsFlagsが負の値だった時の処理
	Type mask = 0;
	if (rhsFlags < 0)
	{
		// rhsFlagsの一番上のビット（符号ビット）をマスクとして設定
		mask |= 1 << (rhs.GetMaxIndex() - 1);

		// 一番上のビットを外す
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
		// オーバーフローで誤作動を起こさないように、uint8_tのサイズに収まるかを確認
		if (indexArray[i] > UINT8_MAX)
		{
			continue;
		}
		uint8_t index = static_cast<uint8_t>(indexArray[i]);
		Set(index, value);
	}
}