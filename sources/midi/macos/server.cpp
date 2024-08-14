#include "midi/other/server.hpp"
#include "config/os.hpp"

#if defined(MSH_APPLE)

//
//
//
///* default constructor */
//msh::midi::server::server(void)
//: _client{"msh midi client"},
//  _source{_client, "msh"},
//  _port{_client, "msh port"} {
//
//	setup_server();
//}
//
///* shared */
//auto msh::midi::server::shared(void) -> ___self& {
//	static ___self instance;
//	return instance;
//}
//
//auto msh::midi::server::setup_server(void) -> void {
//
//	std::cout << "setup server" << std::endl;
//
//	_source.model("version 1.0");
//	_source.manufacturer("midi shell");
//
//	___self::overall_info();
//	___self::source_info();
//
//	//midi::port port{_client};
//	//port.connect(_source);
//
//
//	//port.disconnect(_source);
//
//	//midiGetDevices();
//	//create_port();
//}
//
//
///* note on */
//auto msh::midi::server::note_on(const coremidi::u8 channel,
//								const coremidi::u8 note,
//								const coremidi::u8 velocity) -> void {
//	// add midi to packet
//	___self::shared()._eventlist.note_on(channel, note, velocity);
//}
//
///* note off */
//auto msh::midi::server::note_off(const coremidi::u8 channel,
//								 const coremidi::u8 note) -> void {
//	// add midi to packet
//	___self::shared()._eventlist.note_off(channel, note);
//}
//
///* send midi */
//auto msh::midi::server::send(void) -> void {
//
//	auto& self = ___self::shared();
//
//	// send midi to source device
//	self._eventlist.send(self._source);
//}
//
//
//
//auto string_property(const ::MIDIObjectRef& obj, const ::CFStringRef& id) -> std::string {
//
//	// buffer declaration
//	::CFStringRef cfstring;
//
//	// get string property
//	if (::MIDIObjectGetStringProperty(obj, id, &cfstring) != noErr) {
//		std::cout << "error getting string property" << std::endl;
//		return std::string{};
//	}
//
//	// get property length
//	::CFIndex len = ::CFStringGetLength(cfstring);
//
//	// check if length is not null
//	if (len == 0)
//		return std::string{};
//
//	std::string property;
//
//	property.resize(static_cast<coremidi::u32>(len));
//
//	// copy property to cstring
//	::CFStringGetCString(cfstring, property.data(), len + 1U, kCFStringEncodingASCII);
//
//	// free CFString
//	::CFRelease(cfstring);
//
//	// return allocated string
//	return property;
//}
//
//
//auto msh::midi::server::overall_info(void) -> void {
//
//	// get device number
//	const ::ItemCount device_nbr = ::MIDIGetNumberOfDevices();
//
//
//	// iteration over sources
//	for (std::size_t i = 0U; i < device_nbr; ++i) {
//
//		const ::MIDIDeviceRef device = ::MIDIGetDevice(i);
//
//		std::cout << "device: " << i << std::endl;
//
//		std::cout << string_property(device, kMIDIPropertyName)
//				  << " - "
//				  << string_property(device, kMIDIPropertyModel)
//				  << " - "
//				  << string_property(device, kMIDIPropertyManufacturer)
//				  << std::endl;
//
//		const ::ItemCount entity_nbr = ::MIDIDeviceGetNumberOfEntities(device);
//
//		for (std::size_t z = 0; z < entity_nbr; ++z) {
//
//			const ::MIDIEntityRef entity = ::MIDIDeviceGetEntity(device, z);
//			std::cout << "  entity: " << z << std::endl;
//
//			std::cout << "  " << string_property(entity, kMIDIPropertyName) << " - "
//					  << string_property(entity, kMIDIPropertyModel) << " - "
//					  << string_property(entity, kMIDIPropertyManufacturer) << std::endl;
//
//			const ::ItemCount source_nbr = ::MIDIEntityGetNumberOfSources(entity);
//
//			for (std::size_t y = 0; y < source_nbr; ++y) {
//
//				const ::MIDIEndpointRef source = ::MIDIEntityGetSource(entity, y);
//
//				std::cout << "    [" << string_property(source, kMIDIPropertyName) << "] ["
//						  << string_property(source, kMIDIPropertyModel) << "] ["
//						  << string_property(source, kMIDIPropertyManufacturer) << "]" << std::endl;
//				//std::cout << "    " << string_property(source, kMIDIPropertyModel) << std::endl;
//				//std::cout << "    " << string_property(source, kMIDIPropertyManufacturer) << std::endl;
//
//				//midiObjectGetIntegerProperty(source, kmidiPropertyUniqueID, &id);
//				//std::cout << "source id: " << id << std::endl;
//			}
//		}
//	}
//
//}
//
//void msh::midi::server::source_info(void) {
//
//	ItemCount src = MIDIGetNumberOfSources();
//
//	for (std::size_t x = 0; x < src; ++x) {
//		std::cout << "\x1b[34msource:\x1b[0m " << x << std::endl;
//		MIDIEndpointRef source = MIDIGetSource(x);
//		std::cout << string_property(source, kMIDIPropertyName) << " - "
//				  << string_property(source, kMIDIPropertyModel) << " - "
//				  << string_property(source, kMIDIPropertyManufacturer) << std::endl;
//	}
//
//	ItemCount dst = MIDIGetNumberOfDestinations();
//
//	for (std::size_t x = 0; x < dst; ++x) {
//		std::cout << "\x1b[34mdestination:\x1b[0m " << x << std::endl;
//		MIDIEndpointRef destination = MIDIGetDestination(x);
//		std::cout << string_property(destination, kMIDIPropertyName) << " - "
//				  << string_property(destination, kMIDIPropertyModel) << " - "
//				  << string_property(destination, kMIDIPropertyManufacturer) << std::endl;
//	}
//
//}
//
//
//

#endif // MSH_APPLE
