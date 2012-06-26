/*****************************************************************
 *
 * This file is part of the FLIRTLib project
 *
 * FLIRTLib Copyright (c) 2010 Gian Diego Tipaldi and Kai O. Arras 
 *
 * This software is licensed under the "Creative Commons 
 * License (Attribution-NonCommercial-ShareAlike 3.0)" 
 * and is copyrighted by Gian Diego Tipaldi and Kai O. Arras 
 * 
 * Further information on this license can be found at:
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * 
 * FLIRTLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  
 *
 *****************************************************************/



#ifndef LOGSENSORSTREAM_H_
#define LOGSENSORSTREAM_H_

#include <sensorstream/SensorStream.h>
#include <sensorstream/LogReader.h>
#include <sensorstream/LogWriter.h>
#include <sensorstream/LogReader.h>
#include <sensors/AbstractReading.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/** \def AVG_SIZE_LOG Reserved space for a log in the constructor */
#define AVG_SIZE_LOG 1000 

/** 
 * Representation of log file as a stream of sensor readings.
 * It implements the SensorStream class to stream from log files.
 *
 * See CarmenLogTest.cpp for an example of its use.
 *
 * @author Gian Diego Tipaldi
 */
 
class LogSensorStream: public SensorStream {
    public:
	/** 
	 * Constructor. It creates the stream by giving the _reader and the _writer.
	 * @param _reader The LogReader object for a particular log format.
	 * @param _writer The LogWriter object for a particular log format.
	 */
	LogSensorStream(const LogReader* _reader, const LogWriter* _writer);
	/** Copy Constructor. It copies the object of the class by cloning the readings. */
	LogSensorStream(const LogSensorStream& _stream);
	/**
	 * Assignament operator. It assigns _stream to this object. 
	 * The previous reading are deleted and the _stream one cloned. 
	 */
	LogSensorStream& operator=(const LogSensorStream& _stream);
	/** Destructor */
	virtual ~LogSensorStream();
	
	/** Get the next reading and advance the stream (const reading). */
	virtual const AbstractReading* next() const;
	/** Get the current reading without advancing the stream (const reading). */
	virtual const AbstractReading* current() const;
	/** Seek the stream to a given sensor position. Return false if is not possible. */
	virtual bool seek(const unsigned int _position = 0, SensorStreamOffset _offset = BEGIN);
	/** Get the current sensor position of the stream. Return 0 if it is not seekable */
	virtual inline unsigned int tell() const {return m_index;}
	/** Check if the stream is seekable */
	virtual inline bool isSeekable() const {return true;}
	/** Check if the stream is finished. */
	virtual bool end() const;
	
	/** Get the full log vector. */
	inline const std::vector<AbstractReading*>& getLog() const
	    {return m_log;}
	/** Get the log reader. */
	inline const LogReader* getReader() const
	    {return m_logReader;}
	/** Get the log writer. */
	inline const LogWriter* getWriter() const
	    {return m_logWriter;}
	
	/** Load a log from a file. */
	void load(const std::string& _filename);
	/** Save a log to a file. */
	void save(const std::string& _filename);
    
	/** Load a log from a stream. */
	void load(std::istream& _stream);
	/** Save a log to a stream. */
	void save(std::ostream& _stream);
    
    protected:
	std::vector<AbstractReading*> m_log; /**< The log, represented as a vector of reading. */
	mutable unsigned int m_index; /**< The index of the current reading. */
	const LogReader * m_logReader; /**< The log reader. */
	const LogWriter * m_logWriter; /**< The log writer. */
};

#endif
