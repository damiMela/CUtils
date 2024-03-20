#pragma once

namespace cutils
{
    // Base class template for returning either a value or an error. Error code 0 should be NO_ERROR
    template <typename T, typename ErrorCodeType>
    class Result
    {
    public:
        enum ErrorCode
        {
            NO_ERROR = 0
        };

    public:
        // Constructors
        Result(const T &value) : m_value(value), m_errorCode((ErrorCodeType)NO_ERROR) {}
        Result(ErrorCodeType errorCode) : m_errorCode(errorCode) {}

        // Method to check if the result contains a value
        bool hasValue() const
        {
            return (int)m_errorCode == (int)NO_ERROR;
        }

        // Method to get the value
        T Value() const
        {
            return m_value;
        }

        // Method to get the error code
        ErrorCodeType Error() const
        {
            return m_errorCode;
        }

    private:
        T m_value;
        ErrorCodeType m_errorCode;
    };
}