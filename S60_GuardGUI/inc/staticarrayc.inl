/* Copyright (c) 2004, Nokia. All rights reserved */


// CONSTANTS
_LIT( KStaticArrayPanic,"StaticArray" );

template <class T>
inline const T& TStaticArrayC<T>::operator[]( TInt aIndex ) const
    {
    if ((aIndex >= iCount) || (aIndex < 0))
        {
        Panic( EIndexOutOfBounds );
        }

    return  iArray[aIndex];
    }

template <class T>
inline void TStaticArrayC<T>::Panic( TPanicCode aPanicCode ) const
    {
    User::Panic( KStaticArrayPanic, aPanicCode );
    }

// End of File
