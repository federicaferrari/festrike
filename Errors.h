//!
//! @file: Errors.hpp
//!
//! @author: constantin
//!
//! @date: 10-Apr-2015 8:26:03 AM
//!
//! @ingroup: retrainer/Errors
//!
//! @brief Declaration of the constant collection Errors
//!

//
// Copyright (c) TU Berlin
//
#if !defined(_ERRORS_HEADER_)
#define _ERRORS_HEADER_

   //! @brief Holds Core errors.  This struct is base of the ERROR DATA STRUCT. The
   //! rest of error data structs include this.
   struct errorCore
   {

   public:
      //! @b capemgr directory finding error.  Its value can change, when finding @a
      //! capemgr.X name, at @n
      //! @li findCapeMgrName()  function in Core class.
      bool capeMgrError;

      //! ! @brief @b ocp directory finding error.  Its value can change, when finding @a
      //! ocp.X name, at @n
      //! @li findOcpName()  function in Core class.
      bool ocpError;


      //! @name errorCore
      //!
      //! @brief
      //!
      //!
      //! @retval
      errorCore(){

         capeMgrError    = false;
         ocpError        = false;
      }

   };

   //! @brief Holds CoreADC errors.  This struct holds ADC core errors and includes
   //! pointer of errorCore struct.
   struct errorCoreADC
   {

   public:
      //! Pointer of errorCore struct which stores errors of Core class.  This struct
      //! initializes at constructor of CoreADC class. Its value can set with @n
      //! @li getErrorsFromCore()  function in Core class.
      errorCore* coreErrors;

      //! <b>Device tree</b> loading error.  Its value can change, when loading adc
      //! overlay to device tree, at@n
      //! @li loadDeviceTree()  function in CoreADC class.
      bool dtError;

      //! @b helper directory finding error.  Its value can change, when finding @a
      //! helper.X name, at@n
      //! @li findHelperName()  function in CoreADC class.
      bool helperError;


      //! @name errorCoreADC
      //!
      //! @brief
      //!
      //!
      //! @retval
      errorCoreADC(){

         dtError         = false;
         helperError     = false;
         coreErrors      = new errorCore();
      }

      //! @name errorCoreADC
      //!
      //! @brief
      //!
      //! @param  base
      //! @retval
      errorCoreADC(errorCore* base){

         dtError         = false;
         helperError     = false;
         coreErrors      = base;
      }

   };

   //! @brief Holds ADC errors.  This struct holds ADC errors and includes pointer of
   //! errorCoreADC struct.
   struct errorADC
   {

   public:
      //! Pointer of errorCoreADC struct which stores errors of CoreADC class.  This
      //! struct initializes at constructor of ADC class.@n Its value can set with @n
      //! @li getErrorsFromCoreADC()  function in CoreADC class.
      errorCoreADC* adcCoreErrors;

      //! <b>Value file</b> reading error.  Its value can change, when opening analog
      //! input's value file, at@n
      //! @li getValue()
      //! @li getNumericValue()
      //! @li getConvertedValue()  functions in ADC class.
      bool readError;


      //! @name errorADC
      //!
      //! @brief
      //!
      //!
      //! @retval
      errorADC(){

         readError       = false;
         adcCoreErrors   = new errorCoreADC();
      }

      //! @name errorADC
      //!
      //! @brief
      //!
      //! @param  base
      //! @retval
      errorADC(errorCoreADC* base){

         readError       = false;
         adcCoreErrors   = base;
      }

   };

   //! @brief Holds CoreGPIO errors.  This struct holds GPIO core errors and includes
   //! pointer of errorCore struct.
   struct errorCoreGPIO
   {

   public:
      //! Pointer of errorCore struct, which stores errors of Core class.  This struct
      //! initializes at constructor in CoreGPIO class.@n Its value can set with @n
      //! @li getErrorsFromCore()  function in Core class.
      errorCore* coreErrors;

      //! @b Direction @b file opening error.  Its value can change, when setting
      //! direction of pin, at@n
      //! @li setDirection()  function in CoreGPIO class.
      bool directionFileError;

      //! @b Export @b file opening error.  Its value can change, when exporting pin,
      //! at@n
      //! @li doExport()  function in CoreGPIO class.
      bool exportFileError;


      //! @name errorCoreGPIO
      //!
      //! @brief errorCoreGPIO struct's constructor.  This function clears all flags and
      //! initializes errorCore struct.
      //!
      //!
      //! @retval
      errorCoreGPIO(){

         exportFileError     = false;
         directionFileError  = false;
         coreErrors          = new errorCore();
      }

      //! @name errorCoreGPIO
      //!
      //! @brief errorCoreGPIO struct's constructor with errorCore pointer parameter.
      //!
      //! @param  base
      //! @retval
      errorCoreGPIO(errorCore* base){

         exportFileError     = false;
         directionFileError  = false;
         coreErrors          = base;
      }

   };

   //! @brief Holds GPIO errors.  This struct holds GPIO errors and includes pointer
   //! of errorCoreGPIO struct.
   struct errorGPIO
   {

   public:
      //! ! @brief Pin direction @b couldn't @b set error.  Its value can change, when
      //! checking GPIO pin's direction, at@n
      //! @li isDirectionSet()
      //! @li isReady()
      //! @li getValue()
      //! @li isHigh()
      //! @li toggleValue()
      //! @li setValue()
      //! @li operator>>()
      //! @li operator<<()  functions in BlackGPIO class, if working mode is secureMode.
      //! @sa BlackGPIO::isDirectionSet()
      //! @sa BlackGPIO::isReady()
      //! @sa BlackGPIO::getValue()
      //! @sa BlackGPIO::isHigh()
      //! @sa BlackGPIO::toggleValue()
      //! @sa BlackGPIO::setValue()
      //! @sa BlackGPIO::operator>>(std::string &)
      //! @sa BlackGPIO::operator>>(int &)
      //! @sa BlackGPIO::operator<<(BlackLib::digitalValue)
      bool directionError;

      //! ! @brief Pin @b couldn't @b export error.  Its value can change, when checking
      //! GPIO pin's export status, at@n
      //! @li isExported()
      //! @li isReady()
      //! @li getValue()
      //! @li isHigh()
      //! @li toggleValue()
      //! @li setValue()
      //! @li operator>>()
      //! @li operator<<()  functions in BlackGPIO class, if working mode is secureMode.
      //! @sa BlackGPIO::isExported()
      //! @sa BlackGPIO::isReady()
      //! @sa BlackGPIO::getValue()
      //! @sa BlackGPIO::isHigh()
      //! @sa BlackGPIO::toggleValue()
      //! @sa BlackGPIO::setValue()
      //! @sa BlackGPIO::operator>>(std::string &)
      //! @sa BlackGPIO::operator>>(int &)
      //! @sa BlackGPIO::operator<<(BlackLib::digitalValue)
      bool exportError;

      //! ! @brief Pin @b write forcing error.  Its value can change, when trying to
      //! write something to input type gpio pin, at@n
      //! @li setValue()  function in BlackGPIO class.
      //! @sa BlackGPIO::setValue()
      //! @sa BlackGPIO::operator<<(BlackLib::digitalValue)
      bool forcingError;

      //! ! @brief Pointer of errorCoreGPIO struct, which stores errors of BlackCoreGPIO
      //! class.  This struct initializes at constructor in BlackGPIO class.@n Its value
      //! can set with @n
      //! @li getErrorsFromCoreGPIO()  function in BlackCoreGPIO class.
      //! @sa BlackGPIO::BlackGPIO()
      //! @sa BlackCoreGPIO::getErrorsFromCoreGPIO()
      errorCoreGPIO* gpioCoreErrors;

      //! ! @brief @b Value @b file reading error.  Its value can change, when opening
      //! gpio pin's value file, at@n
      //! @li getValue()
      //! @li getNumericValue()
      //! @li isHigh()
      //! @li toggleValue()
      //! @li operator>>()  functions in BlackGPIO class.
      //! @sa BlackGPIO::getValue()
      //! @sa BlackGPIO::getNumericValue()
      //! @sa BlackGPIO::isHigh()
      //! @sa BlackGPIO::toggleValue()
      //! @sa BlackGPIO::operator>>(std::string &)
      //! @sa BlackGPIO::operator>>(int &)
      bool readError;

      //! ! @brief @b Value @b file writing error.  Its value can change, when opening
      //! gpio pin's value file, at@n
      //! @li setValue()
      //! @li operator<<()  function in BlackGPIO class.
      //! @sa BlackGPIO::setValue()
      //! @sa BlackGPIO::operator<<(BlackLib::digitalValue)
      bool writeError;


      //! @name errorGPIO
      //!
      //! @brief ! @brief errorGPIO struct's constructor.  This function clears all flags
      //! and initializes errorCoreGPIO struct.
      //!
      //!
      //! @retval
      errorGPIO(){

         exportError     = false;
         directionError  = false;
         readError       = false;
         writeError      = false;
         forcingError    = false;
         gpioCoreErrors  = new errorCoreGPIO();
      }

      //! @name errorGPIO
      //!
      //! @brief ! @brief errorGPIO struct's constructor with errorCoreGPIO pointer
      //! parameter.
      //! @param [in] *base    pointer of errorCoreGPIO struct.  This function clears all
      //! flags and assigns input parameter to gpioCoreErrors variable.
      //!
      //! @param  base
      //! @retval
      errorGPIO(errorCoreGPIO* base){

         exportError     = false;
         directionError  = false;
         readError       = false;
         writeError      = false;
         forcingError    = false;
         gpioCoreErrors  = base;
      }

   };

//   //! @brief Holds SPI errors.  This struct holds SPI errors and includes pointer of
//   //! errorCore struct.
//   struct errorSPI
//   {
//
//   public:
//      //! ! @brief SPI's @b bit @b size property setting error.  Its value can change,
//      //! when setting spi's bit size property, at@n
//      //! @li setBitsPerWord()
//      //! @li getBitsPerWord()
//      //! @li setProperties()
//      //! @li getProperties()  functions in BlackSPI class.
//      //! @sa BlackSPI::setBitsPerWord()
//      //! @sa BlackSPI::getBitsPerWord()
//      //! @sa BlackSPI::setProperties()
//      //! @sa BlackSPI::getProperties()
//      bool bitSizeError;
//
//      //! TTY file @b closing error.  Its value can change, when closing spi's tty file,
//      //! at@n
//      //! @li close()  function in SPI class.
//      //! @sa SPI::close()
//      bool closeError;
//
//      //! Pointer of errorCore struct, which stores errors of Core class.  This struct
//      //! initializes at constructor in SPI class.@n Its value can set with @n
//      //! @li getErrorsFromCore()  function in SPI class.
//      errorCore* coreErrors;
//
//      //! @b Device @b tree loading error.  Its value can change, when loading spi
//      //! overlay to device tree, at@n
//      //! @li loadDeviceTree()  function in SPI class.
//      bool dtError;
//
//      //! ! @brief SPI's @b mode property setting error.  Its value can change, when
//      //! setting spi's mode property, at@n
//      //! @li setMode()
//      //! @li getMode()
//      //! @li setProperties()
//      //! @li getProperties()  functions in SPI class.
//      bool modeError;
//
//      //! ! @brief TTY file @b opening error.  Its value can change, when opening spi's
//      //! tty file, at@n
//      //! @li open()  function in SPI class.
//      bool openError;
//
//      //! ! @brief TTY file path finding error.  Its value can change, when finding spi's
//      //! tty file path, at@n
//      //! @li findPortPath()  function in SPI class.
//      //! @sa SPI::findPortPath()
//      bool portPathError;
//
//      //! ! @brief SPI's @b speed property setting error.  Its value can change, when
//      //! setting spi's speed property, at@n
//      //! @li setMaximumSpeed()
//      //! @li getMaximumSpeed()
//      //! @li setProperties()
//      //! @li getProperties()  functions in SPI class.
//      bool speedError;
//
//      //! ! @brief SPI data transfer error.  Its value can change, when transfering data
//      //! between master and slave, at@n
//      //! @li transfer()
//      //! @li operator<<()  function in SPI class.
//      bool transferError;
//
//
//      //! @name errorSPI
//      //!
//      //! @brief errorSPI struct's constructor.  This function clears all flags and
//      //! initializes errorCore struct.
//      //!
//      //!
//      //! @retval
//      errorSPI(){
//
//         dtError         = false;
//         openError       = false;
//         closeError      = false;
//         portPathError   = false;
//         transferError   = false;
//         modeError       = false;
//         speedError      = false;
//         bitSizeError    = false;
//         coreErrors      = new errorCore();
//      }
//
//      //! @name errorSPI
//      //!
//      //! @brief errorSPI struct's constructor with errorCore pointer parameter.
//      //!
//      //! @param  base
//      //! @retval
//      errorSPI(errorCore* base){
//
//         dtError         = false;
//         openError       = false;
//         closeError      = false;
//         portPathError   = false;
//         transferError   = false;
//         modeError       = false;
//         speedError      = false;
//         bitSizeError    = false;
//         coreErrors      = base;
//      }
//
//   };

   //! @brief Holds BlackCorePWM errors.  This struct holds PWM core errors and
   //! includes pointer of errorCore struct.
   struct errorCorePWM
   {

   public:
      //! Pointer of errorCore struct which stores errors of Core class.  This struct
      //! initializes at constructor in CorePWM class.@n Its value can set with @n
      //! @li getErrorsFromCore()  function in Core class.
      errorCore* coreErrors;

      //! @b Device @b tree loading error.  Its value can change, when loading pwm
      //! overlay to device tree, at@n
      //! @li loadDeviceTree()  function in CorePWM class.
      bool dtError;

      //! @b Device @b tree loading error.  Its value can change, when loading subsystem
      //! pwm overlay to device tree, at@n
      //! @li loadDeviceTree()  function in CorePWM class.
      bool dtSsError;

      //! @b pwm_test directory finding error.  Its value can change, when finding @a
      //! pwm_test_X.Y name, at@n
      //! @li findPwmTestName()  function in CorePWM class.
      bool pwmTestError;


      //! @name errorCorePWM
      //!
      //! @brief errorCorePWM struct's constructor.  This function clears all flags and
      //! initializes errorCore struct.
      //!
      //!
      //! @retval
      errorCorePWM(){

         dtSsError       = false;
         dtError         = false;
         pwmTestError    = false;
         coreErrors      = new errorCore();
      }

      //! @name errorCorePWM
      //!
      //! @brief errorCorePWM struct's constructor with errorCore pointer parameter.
      //! @param [in] *base    pointer of errorCore struct.  This function clears all
      //! flags and assigns input parameter to coreErrors variable.
      //!
      //! @param  base
      //! @retval
      errorCorePWM(errorCore* base){

         dtSsError       = false;
         dtError         = false;
         pwmTestError    = false;
         coreErrors      = base;
      }

   };

   //! @brief ! @brief Holds BlackPWM errors.  This struct holds PWM errors and
   //! includes pointer of errorCorePWM struct.
   struct errorPWM
   {

   public:
      //! @b Duty @b file reading error.  Its value can change, when opening pwm's duty
      //! value file, at@n
      //! @li getValue()
      //! @li getNumericValue()
      //! @li getDutyValue()
      //! @li getNumericDutyValue()
      //! @li setDutyPercent()
      //! @li setPeriodTime()
      //! @li setSpaceRatioTime()
      //! @li setLoadRatioTime()  functions in PWM class.
      bool dutyFileError;

      //! Out of range value error.  Its value can change, when setting some variables of
      //! pwm, at@n
      //! @li setDutyPercent()
      //! @li setPeriodTime()
      //! @li setSpaceRatioTime()
      //! @li setLoadRatioTime()  functions in PWM class.
      bool outOfRange;

      //! @b Period @b file reading error.  Its value can change, when opening pwm's
      //! period value file, at@n
      //! @li getValue()
      //! @li getNumericValue()
      //! @li getPeriodValue()
      //! @li getNumericPeriodValue()
      //! @li setPeriodTime()
      //! @li setSpaceRatioTime()
      //! @li setLoadRatioTime()  functions in PWM class.
      bool periodFileError;

      //! @b Polarity @b file reading error.  Its value can change, when opening pwm's
      //! polarity value file, at@n
      //! @li getPolarityValue()
      //! @li isPolarityStraight()
      //! @li isPolarityReverse()
      //! @li setPolarity()
      //! @li tooglePolarity()  functions in PWM class.
      bool polarityFileError;

      //! Pointer of errorCorePWM struct, which stores errors of CorePWM class.  This
      //! struct initializes at constructor in PWM class.@n Its value can set with @n
      //! @li getErrorsFromCorePWM()  function in CorePWM class.
      errorCorePWM* pwmCoreErrors;

      //! @b Run @b file reading error.  Its value can change, when opening pwm's run
      //! value file, at@n
      //! @li getRunValue()
      //! @li isRunning()
      //! @li setRunState()
      //! @li toggleRunState()  functions in PWM class.
      bool runFileError;


      //! @name errorPWM
      //!
      //! @brief errorPWM struct's constructor.  This function clears all flags and
      //! initializes errorCorePWM struct.
      //!
      //!
      //! @retval
      errorPWM(){

         periodFileError     = false;
         dutyFileError       = false;
         runFileError        = false;
         polarityFileError   = false;
         outOfRange          = false;
         pwmCoreErrors       = new errorCorePWM();
      }

      //! @name errorPWM
      //!
      //! @brief errorPWM struct's constructor with errorCorePWM pointer parameter.
      //! @param [in] *base    pointer of errorCorePWM struct.  This function clears all
      //! flags and assigns input parameter to pwmCoreErrors variable.
      //!
      //! @param  base
      //! @retval
      errorPWM(errorCorePWM* base){

         periodFileError     = false;
         dutyFileError       = false;
         runFileError        = false;
         polarityFileError   = false;
         outOfRange          = false;
         pwmCoreErrors       = base;
      }

   };

   //! @brief Holds I2C errors.  This struct holds I2C errors and includes pointer of
   //! errorCore struct.
   struct errorI2C
   {

   public:
      //! TTY file @b closing error.  Its value can change, when closing i2c's tty file,
      //! at@n
      //! @li close()  function in I2C class.
      bool closeError;

      //! Pointer of errorCore struct, which stores errors of Core class.  This struct
      //! initializes at constructor in I2C class.@n Its value can set with @n
      //! @li getErrorsFromCore()  function in I2C class.
      errorCore* coreErrors;

      //! TTY file @b opening error.  Its value can change, when opening i2c's tty file,
      //! at@n
      //! @li open()  function in I2C class.
      bool openError;

      //! I2C @b reading error.  Its value can change, when reading i2c data, at@n
      //! @li readByte()
      //! @li readWord()
      //! @li readBlock()
      //! @li readLine()  functions in I2C class.
      bool readError;

      //! Slave setting error.  Its value can change, when opening TTY file, doing i2c
      //! write/read operations and assigning new device address value at@n
      //! @li open()
      //! @li writeByte()
      //! @li writeWord()
      //! @li writeBlock()
      //! @li writeLine()
      //! @li readByte()
      //! @li readWord()
      //! @li readBlock()
      //! @li readLine()
      //! @li setDeviceAddress()  functions in I2C class.
      bool setSlaveError;

      //! I2C @b writing error.  Its value can change, when writing i2c data, at@n
      //! @li writeByte()
      //! @li writeWord()
      //! @li writeBlock()
      //! @li writeLine()  functions in I2C class.
      bool writeError;


      //! @name errorI2C
      //!
      //! @brief I2C struct's constructor.  This function clears all flags and
      //! initializes errorCore struct.
      //!
      //!
      //! @retval
      errorI2C(){

         openError       = false;
         closeError      = false;
         setSlaveError   = false;
         readError       = false;
         writeError      = false;
         coreErrors      = new errorCore();
      }

      //! @name errorI2C
      //!
      //! @brief I2C struct's constructor with errorCore pointer parameter.
      //! This function clears all flags and assigns input parameter to coreErrors
      //! variable.
      //!
      //! @param  base
      //! @retval
      errorI2C(errorCore* base){

         openError       = false;
         closeError      = false;
         setSlaveError   = false;
         readError       = false;
         writeError      = false;
         coreErrors      = base;
      }

   };

   //! @brief Holds BlackUART errors.  This struct holds UART errors and includes
   //! pointer of errorCore struct.
   struct errorUART
   {

   public:
      //! UART's @b baud property setting error.  Its value can change, when setting
      //! uart's baud property, at@n
      bool baudRateError;

      //! UART's @b character @b size property setting error.  Its value can change, when
      //! setting uart's character size property, at@n
      bool charSizeError;

      //! TTY file @b closing error.  Its value can change, when closing uart's tty file,
      //! at@n
      bool closeError;

      //! Pointer of errorCore struct, which stores errors of BlackCore class.  This
      //! struct initializes at constructor in BlackUART class.@n Its value can set with
      //! @n
      //! @li getErrorsFromCore()  function in UART class.
      errorCore* coreErrors;

      //! Some uart operation's direction error.  Its value can change, when doing some
      //! operations to UART, at@n
      bool directionError;

      //! @b Device @b tree loading error.  Its value can change, when loading uart
      //! overlay to device tree, at@n
      //! @li loadDeviceTree()  function in UART class.
      bool dtError;

      //! UART line flushing error.  Its value can change, when flushing line, at@n
      //! @li flush()  function in UART class.
      bool flushError;

      //! TTY file @b opening error.  Its value can change, when opening uart's tty file,
      //! at@n
      //! @li open()  function in UART class.
      bool openError;

      //! UART's @b parity property setting error.  Its value can change, when setting
      //! uart's parity property, at@n
      //! @li getParity()
      //! @li setParity()
      //! @li getProperties()
      //! @li setProperties()  functions in UART class.
      bool parityError;

      //! TTY file @b reading error.  Its value can change, when reading uart's tty file,
      //! at@n
      //! @li read()
      //! @li transfer()
      //! @li operator>>()  functions in UART class.
      bool readError;

      //! UART's @b stop @b bits property setting error.  Its value can change, when
      //! setting uart's stop bits property, at@n
      //! @li getStopBits()
      //! @li setParity()
      //! @li getProperties()
      //! @li setProperties()  functions inUART class.
      bool stopBitsError;

      //! TTY file @b writing error.  Its value can change, when writing uart's tty file,
      //! at@n
      //! @li write()
      //! @li transfer()
      //! @li operator<<()  functions in ART class.
      bool writeError;


      //! @name errorUART
      //!
      //! @brief errorUART struct's constructor.  This function clears all flags and
      //! initializes errorCore struct.
      //!
      //!
      //! @retval
      errorUART(){

         dtError         = false;
         openError       = false;
         closeError      = false;
         directionError  = false;
         flushError      = false;
         readError       = false;
         writeError      = false;
         baudRateError   = false;
         parityError     = false;
         stopBitsError   = false;
         charSizeError   = false;
         coreErrors      = new errorCore();
      }

      //! @name errorUART
      //!
      //! @brief errorUART struct's constructor with errorCore pointer parameter.
      //!
      //! This function clears all flags and assigns input parameter to coreErrors
      //! variable.
      //!
      //! @param  base
      //! @retval
      errorUART(errorCore* base){

         dtError         = false;
         openError       = false;
         closeError      = false;
         directionError  = false;
         flushError      = false;
         readError       = false;
         writeError      = false;
         baudRateError   = false;
         parityError     = false;
         stopBitsError   = false;
         charSizeError   = false;
         coreErrors      = base;
      }

   };
#endif // !defined(_ERRORS_HEADER_)
