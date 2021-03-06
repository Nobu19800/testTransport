// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*! 
 * @file InterfaceDataTypesPublisher.cpp
 * This file contains the implementation of the publisher functions.
 *
 * This file was generated by the tool fastcdrgen.
 */


#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/publisher/Publisher.h>
#include <fastrtps/attributes/PublisherAttributes.h>

#include <fastrtps/Domain.h>
#include <fastrtps/xmlparser/XMLProfileManager.h>

#include <fastrtps/utils/eClock.h>
#include <chrono>
#include <thread>

#include "InterfaceDataTypesPublisher.h"

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

InterfaceDataTypesPublisher::InterfaceDataTypesPublisher() : mp_participant(nullptr), mp_publisher(nullptr) {}

InterfaceDataTypesPublisher::~InterfaceDataTypesPublisher() {	Domain::removeParticipant(mp_participant);}

bool InterfaceDataTypesPublisher::init(std::string xml_name)
{
	// Create RTPSParticipant


	if(!xml_name.empty())
	{
		eprosima::fastrtps::Domain::loadXMLProfilesFile(xml_name);
	}
	
	if(xml_name.empty())
	{
		ParticipantAttributes PParam;
		PParam.rtps.builtin.domainId = 0;
		PParam.rtps.builtin.leaseDuration = c_TimeInfinite;
		PParam.rtps.builtin.readerHistoryMemoryPolicy = eprosima::fastrtps::rtps::PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
		PParam.rtps.builtin.writerHistoryMemoryPolicy = eprosima::fastrtps::rtps::PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
		PParam.rtps.setName("Participant_publisher");  //You can put here the name you want
		mp_participant = Domain::createParticipant(PParam);
	}
	else
	{
		mp_participant = Domain::createParticipant("participant_profile");
	}
	if(mp_participant == nullptr)
		return false;
	
	//Register the type
	
	Domain::registerType(mp_participant,(TopicDataType*) &myType);
	
	// Create Publisher
	
	PublisherAttributes Wparam;
	if(xml_name.empty())
	{
		Wparam.topic.topicKind = NO_KEY;
		Wparam.topic.topicDataType = myType.getName();  //This type MUST be registered
		Wparam.topic.topicName = "chatter";
		Wparam.qos.m_publishMode.kind = ASYNCHRONOUS_PUBLISH_MODE;
		Wparam.historyMemoryPolicy = eprosima::fastrtps::rtps::PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
		Wparam.qos.m_reliability.kind = eprosima::fastrtps::RELIABLE_RELIABILITY_QOS;
		//Wparam.topic.historyQos.kind = KEEP_ALL_HISTORY_QOS;
	}
	else
	{
		if(eprosima::fastrtps::xmlparser::XMLP_ret::XML_ERROR == eprosima::fastrtps::xmlparser::XMLProfileManager::fillPublisherAttributes("publisher_profile", Wparam))
		{
			return false;
		}
		else
		{
			Wparam.topic.topicDataType = myType.getName();  //This type MUST be registered
		}
	}
	mp_publisher = Domain::createPublisher(mp_participant,Wparam,(PublisherListener*)&m_listener);
	if(mp_publisher == nullptr)
		return false;
	std::cout << "Publisher created, waiting for Subscribers." << std::endl;
	return true;
}

void InterfaceDataTypesPublisher::PubListener::onPublicationMatched(Publisher* pub,MatchingInfo& info)
{
	if (info.status == MATCHED_MATCHING)
	{
		n_matched++;
		std::cout << "Publisher matched" << std::endl;
	}
	else
	{
		n_matched--;
		std::cout << "Publisher unmatched" << std::endl;
	}
}

void InterfaceDataTypesPublisher::run()
{
	while(m_listener.n_matched == 0)
	{
		eClock::my_sleep(250); // Sleep 250 ms
	}

    static double logmul[] = { 2.0, 2.5, 2.0 };
    int datasize = 100;
    const int maxsize = 1200001;
    int count = 0;
    const int datacount = 500;
	
	// Publication code
	
	RTC::CameraImage st;

    auto sleep_nsec = std::chrono::nanoseconds(1000000000/500);

	
	/* Initialize your structure here */
	
	do
	{
            if(datasize < 300)
            {
                st.height(1);
            }
            else
            {
                st.height(100);
            }
        
            st.width(datasize / st.height() / 3);
            st.pixels().resize(st.height()*st.width() * 3);
            auto now = std::chrono::system_clock::now().time_since_epoch();
            auto sec = std::chrono::duration_cast<std::chrono::seconds>(now);
            auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(now - sec);
            st.tm().sec(static_cast<unsigned int>(sec.count()));
            st.tm().nsec(static_cast<unsigned int>(nsec.count()));
            mp_publisher->write(&st);
            std::this_thread::sleep_for(sleep_nsec);
            ++count;

            if (count%datacount == 0)
            {
                std::cout << st.height()*st.width() * 3 << std::endl;
                datasize = static_cast<int>(static_cast<double>(datasize)*logmul[(count / datacount) % 3]);
            }

	}while(datasize < maxsize);

    std::cout << "finish" << std::endl;
}
