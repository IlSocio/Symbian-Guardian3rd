/* Copyright (c) 2004, Nokia. All rights reserved */


#ifndef __STATIC_ARRAY_C_H__
#define __STATIC_ARRAY_C_H__



/**
* TStaticArrayC
* This templated class provides a type, and size, safe method of
* using static arrays.
*/
template <class T>
class TStaticArrayC
    {
    public:

        /**
        * operator[]
        * Return an element from the array.
        * @param aIndex the index of the element to return
        * @return a reference to the object
        */
        inline const T& operator[]( TInt aIndex ) const;

        /**
        * TPanicCode
        * Panic code
        * EIndexOutOfBounds index is out of bounds
        */
        enum TPanicCode
            { 
                EIndexOutOfBounds = 1 
            };

        /**
        * Panic
        * Generate a panic.
        * @param aPanicCode the reason code for the panic
        */
        inline void Panic( TPanicCode aPanicCode ) const;

    public: // data

        /** iArray the array of elements */
        const T* iArray;

        /** iCount the number of elements */
        TInt iCount;

    };

// INCLUDES
#include "StaticArrayC.inl"

/**
* CONSTRUCT_STATIC_ARRAY_C
* Initalise a global constant of type TStaticArrayC<>.
* @param aValue the underlying const array of T
*/
#define CONSTRUCT_STATIC_ARRAY_C( aValue ) \
        {   \
        aValue,    \
        sizeof( aValue ) / sizeof( *aValue )  \
        }  \

#endif //   __STATIC_ARRAY_C_H__

// End of File
