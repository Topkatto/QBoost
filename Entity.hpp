#include <iostream>
#include <functional>
#include <vector>
inline bool __ENTITY_DEBUG_ENABLED = false;

namespace qboost
{
    template <typename T>
    struct entity
    {
    private:
        T ENTITY_VAL;
        std::function<bool(const T&)> ENTITY_VALIDATOR = [](const T& val) {
            return true;
        };
        std::vector<T> ENTITY_STATES;

    public:
        T EntityValue;

        entity() = default;
        entity(T object) : ENTITY_VAL(object), EntityValue(object) {}


        void SetValidator(const std::function<bool(const T&)>& b) {
            if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: _SetValidator called)\n"; }
            ENTITY_VALIDATOR = b;
            if (ENTITY_VALIDATOR(ENTITY_VAL) == false)
            {
                ENTITY_VAL = T{};
            }
        }

        std::function<bool(const T&)> GetValidator() const {
            if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: _GetValidator called)\n"; }
            return ENTITY_VALIDATOR;
        }

        bool EntitySet(const T& object) {
            if (ENTITY_VALIDATOR(object)) {
                if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: EntitySet succeeded)\n"; }
                ENTITY_VAL = object;
                EntityValue = object;
                return true;
            } else {
                if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG_WARN: The value you are trying to set violates the validator function. This is likely not what you want!)\n"; }
                return false;
            }
        }

        T EntityGet() const {
            if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: _EntityGet called)\n"; }
            return ENTITY_VAL;
        }

        void UpdateEntity() {
            if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: _UpdateEntity called)\n"; }
            EntitySet(EntityValue);
        }

        int SaveState()
        {
            if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: _SaveState called)\n"; }
            ENTITY_STATES.push_back((*this).ENTITY_VAL);
            return (int) ENTITY_STATES.size()-1;
        }

        entity<T> GetState(int __INDEX)
        {
            if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: _GetState called)\n"; }
            return entity<T>(ENTITY_STATES[__INDEX]);
        }

        void LoadState(int __INDEX)
        {
            if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: _SetState called)\n"; }
            (*this) = ENTITY_STATES[__INDEX];
        }

        void ClearStates()
        {
            if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: _ClearENTITY_STATES called)\n"; }
            ENTITY_STATES.clear();
        }

        void EraseEntity()
        {
            (*this).ENTITY_VAL = T{};
            EntityValue = T{};
        }


        entity<T>& operator=(const T& rhs) { EntitySet(rhs); return *this; }
        entity<T>& operator+=(const T& rhs) { EntitySet(ENTITY_VAL + rhs); return *this; }
        entity<T>& operator-=(const T& rhs) { EntitySet(ENTITY_VAL - rhs); return *this; }
        entity<T>& operator*=(const T& rhs) { EntitySet(ENTITY_VAL * rhs); return *this; }
        entity<T>& operator/=(const T& rhs) { EntitySet(ENTITY_VAL / rhs); return *this; }
        entity<T>& operator%=(const T& rhs) { EntitySet(ENTITY_VAL % rhs); return *this; }
        entity<T>& operator&=(const T& rhs) { EntitySet(ENTITY_VAL & rhs); return *this; }
        entity<T>& operator|=(const T& rhs) { EntitySet(ENTITY_VAL | rhs); return *this; }
        entity<T>& operator^=(const T& rhs) { EntitySet(ENTITY_VAL ^ rhs); return *this; }
        entity<T>& operator<<=(const T& rhs) { EntitySet(ENTITY_VAL << rhs); return *this; }
        entity<T>& operator>>=(const T& rhs) { EntitySet(ENTITY_VAL >>= rhs); return *this; }

        entity<T>& operator++() { EntitySet(ENTITY_VAL + 1); return *this; }
        entity<T> operator++(int) { entity<T> temp = *this; EntitySet(ENTITY_VAL + 1); return temp; }
        entity<T>& operator--() { EntitySet(ENTITY_VAL - 1); return *this; }
        entity<T> operator--(int) { entity<T> temp = *this; EntitySet(ENTITY_VAL - 1); return temp; }

        operator const T&() const { return ENTITY_VAL; }

        entity<T> operator+(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: + op)\n"; } return Entity(ENTITY_VAL + rhs); }
        entity<T> operator-(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: - op)\n"; } return Entity(ENTITY_VAL - rhs); }
        entity<T> operator*(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: * op)\n"; } return Entity(ENTITY_VAL * rhs); }
        entity<T> operator/(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: / op)\n"; } return Entity(ENTITY_VAL / rhs); }
        entity<T> operator%(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: % op)\n"; } return Entity(ENTITY_VAL % rhs); }

        entity<T> operator&(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: & op)\n"; } return Entity(ENTITY_VAL & rhs); }
        entity<T> operator|(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: | op)\n"; } return Entity(ENTITY_VAL | rhs); }
        entity<T> operator^(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: ^ op)\n"; } return Entity(ENTITY_VAL ^ rhs); }
        entity<T> operator<<(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: << op)\n"; } return Entity(ENTITY_VAL << rhs); }
        entity<T> operator>>(const T& rhs) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: >> op)\n"; } return Entity(ENTITY_VAL >> rhs); }
        entity<T> operator~() const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: ~ op)\n"; } return Entity(~ENTITY_VAL); }

        bool operator!() const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: ! op)\n"; } return !ENTITY_VAL; }
        bool operator&&(const entity<T>& other) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: && op)\n"; } return ENTITY_VAL && other.ENTITY_VAL; }
        bool operator||(const entity<T>& other) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: || op)\n"; } return ENTITY_VAL || other.ENTITY_VAL; }

        bool operator==(const entity<T>& other) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: == op)\n"; } return ENTITY_VAL == other.ENTITY_VAL; }
        bool operator!=(const entity<T>& other) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: != op)\n"; } return ENTITY_VAL != other.ENTITY_VAL; }
        bool operator<(const entity<T>& other) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: < op)\n"; } return ENTITY_VAL < other.ENTITY_VAL; }
        bool operator>(const entity<T>& other) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: > op)\n"; } return ENTITY_VAL > other.ENTITY_VAL; }
        bool operator<=(const entity<T>& other) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: <= op)\n"; } return ENTITY_VAL <= other.ENTITY_VAL; }
        bool operator>=(const entity<T>& other) const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: >= op)\n"; } return ENTITY_VAL >= other.ENTITY_VAL; }

        T& operator*() { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: * (deref) op)\n"; } return ENTITY_VAL; }
        const T& operator*() const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: const * (deref) op)\n"; } return ENTITY_VAL; }
        T* operator->() { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: -> op)\n"; } return &ENTITY_VAL; }
        const T* operator->() const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: const -> op)\n"; } return &ENTITY_VAL; }

        template<typename Index>
        auto operator[](Index&& i) { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: [] op)\n"; } return ENTITY_VAL[std::forward<Index>(i)]; }
        const T& operator()() const { if (__ENTITY_DEBUG_ENABLED) { std::cout << "(DEBUG: () op)\n"; } return ENTITY_VAL; }
    };
}