# SRIP Final Report

### Abstract

Air pollution is one of the major health risks in countries like India which has the worst air quality globally. Personal exposure monitoring is essential as most health-related studies consider the data from centrally located air quality monitors to assess particulate matter(PM)-related exposure. The proposed project involves designing and developing an in-house low-cost air quality monitor using Arduino and other modules. Later stages include converting it to a field deploy-able monitor by packaging it in a 3D-printed housing assembly. The monitoring device will capture the daily PM data of the subject in ambient as well as indoor micro environments. Detailed time activity information will help estimate the extent of adverse effects using different health exposure models. The study will provide the true estimate of individual exposure to particulates during the entire day.

### Background

Approximately 1.67 million deaths in India in 2019 were linked to air pollution, accounting for around 17.8% of the total deaths in the country. The main contributors to these fatalities were outdoor particulate matter pollution, which accounted for 0.98 million deaths, and household air pollution, responsible for 0.61 million deaths [1]. Measurements of temporal and spatial changes of concentrations are vital to understanding pollution characteristics, which is not possible with high cost scientific instruments [2]. Low-cost monitors offer an opportunity to collect high-density temporal and spatial data [3]. To address this challenge, there is a need for efficient and accessible air pollution monitoring systems that can provide real-time data on pollutant levels. This research proposal aims to develop a low-cost and portable air pollution monitoring device that accurately measures particulate matter (PM) levels in the ambient air. The device will empower individuals and communities to monitor air quality in their surroundings, enabling them to make informed decisions regarding their health and well-being.

### Literature Review

Li et al. (Optical Characterization Studies of a Low-Cost Particle Sensor) have used the Sharp GP2Y1010AU0F (Model GP2Y) low cost sensor to make their monitoring device, and an Arduino Nano (Atmega328P) as their micro-controller which sent data via an XBee Series 2 wireless module [4].  Bulot et al. (Long-term field comparison of multiple low-cost particulate matter sensors in an outdoor urban environment) have compared the PMS5003 with the GRIMM EDM 180 dust monitor as standard reference instrument [5].

### System Architecture

![mermaid-diagram-2023-07-07-052037.png](SRIP%20Final%20Report%20355d48071ea740b4b49a7ed5b7c8418f/mermaid-diagram-2023-07-07-052037.png)

The system architecture diagram depicts the overall design of our IoT-enabled air quality monitoring system. The hardware components, including the PMS5003 particulate matter sensor, DHT11 temperature and humidity sensor, and the Memory Card Module for data storage, are shown in the "Hardware" subgraph. These components are connected to the NodeMCU V3 microcontroller, which acts as the central processing unit. The DHT11 communicates with the NodeMCU V3 via a one-wire protocol, involving a three-step process of sending a request, receiving a response pulse, and transmitting 40 bits of data. On the other hand, the PMS5003 uses a UART protocol with RX and TX ports to send data packets containing PM1.0, PM2.5, and PM10 data, along with various particle number concentrations (gt03, 05, 10, 25, 50, 100). The NodeMCU V3 appends the sensor data, including particulate matter, temperature, and humidity, to a JSON object and stores it in a CSV file on the Memory Card Module using the SPI protocol. Simultaneously, the NodeMCU V3 publishes the same sensor data JSON object to Mosquitto, an MQTT broker running on our R-pi server, through the MQTT protocol. The Mosquitto instance forwards the data stream to Node-RED, which listens to the MQTT stream, extracts the JSON object, and utilizes the Chart Module to create real-time visualizations of the data. These live charts can be accessed via a web browser on any device by opening the link to the NodeMCU V3. The system architecture provides a robust and efficient means of monitoring air quality in real-time while offering data storage capabilities and remote data visualization.

### Hardware Design

- Component Selection
    
    The selection of components for our air quality monitoring system was based on several crucial factors to ensure the effectiveness and practicality of the design. For measuring particulate matter concentrations, we opted for the PMS5003 sensor. This choice was influenced by its widespread use in numerous research papers, proving its reliability and accuracy. Additionally, the PMS5003's affordability made it a cost-effective option for our project.
    
    To serve as the central processing unit and facilitate data communication, we selected the NodeMCU microcontroller. Its built-in Wi-Fi capability was a critical factor in enabling seamless data transmission to our remote server. The integrated Real-Time Clock (RTC) functionality allowed us to timestamp the collected data accurately. Moreover, the NodeMCU's compact form factor and low-cost made it an ideal choice for integration into our air quality monitoring device. Its ability to be powered via a micro USB cable added to its convenience and ease of use.
    
    For measuring temperature and humidity, the DHT11 sensor proved to be a suitable choice. Its reliable temperature and humidity measuring capabilities were essential for providing additional environmental data in our monitoring system. Furthermore, the DHT11's simplicity and affordability complemented our goal of creating an efficient and cost-effective solution.
    
    To ensure data backup and offline storage capabilities, we integrated an SD card module into the system. This module allows us to save the collected data locally in case of any connectivity issues, ensuring data integrity and resilience.
    
    Overall, our component selection process aimed at creating a robust, cost-effective, and practical air quality monitoring device, incorporating well-established sensors with proven capabilities and leveraging the NodeMCU's versatile features for seamless data communication.
    
- Outer housing
    
    In the design process of the 3D casing for our air quality monitoring device using Fusion 360, a key focus was to achieve a compact and efficient layout. By utilizing existing models of the sensors, we strategically arranged them to optimize space usage. Notably, the PMS5003's metal body served a dual purpose, functioning as both the sensor's casing and a heat-sink  for the NodeMCU microcontroller, ensuring effective heat dissipation. To further economize space, we ingeniously nestled the SD card module between the pins of the NodeMCU, allowing for a more efficient utilization of available real estate within the casing. We also meticulously designed openings in the casing to facilitate the PMS5003's inlet and exhaust, ensuring proper air circulation for accurate measurements. Additionally, we incorporated an opening for the charging port of the NodeMCU and a separate slot for the memory card, providing easy access to these essential functionalities. To secure the top cover of the casing, we implemented M2 bolts, ensuring a robust and reliable closure. The resulting 3D design presented a streamlined and sleek enclosure, successfully accommodating all the components while maintaining a space-saving footprint for our air quality monitoring device.
    
    ![housing_a v3 (~recovered).png](SRIP%20Final%20Report%20355d48071ea740b4b49a7ed5b7c8418f/housing_a_v3_(recovered).png)
    
- 3d printing
    
    Using the Creality Ender 3 3D printer and white PLA filament, we 3D printed the compact casing for our air quality monitoring device. The Ender 3's precision and reliability ensured a smooth finish, while the white PLA material provided a visually appealing and durable enclosure. The printer's efficiency allowed us to produce the final casing with optimal dimensions, accommodating all the necessary sensors and components effectively.
    
    ![Untitled](SRIP%20Final%20Report%20355d48071ea740b4b49a7ed5b7c8418f/Untitled.png)
    
- Circuit Diagrams
    
    3 custom ports were created, one each for the PMS5003, SD card module, and DHT11. The PMS5003 port has 4 pins. The SD card module port has 6 pins. And the DHT11 port has 3 pins. They were connected to the appropriate pins of the nodeMCU in the schematic section of Eagle CAD PCB design software. 
    

![Untitled](SRIP%20Final%20Report%20355d48071ea740b4b49a7ed5b7c8418f/Untitled%201.png)

- PCB Design
    
    The schematic was converted to a board design in Eagle CAD. And the components were placed in appropriate orientation and distance with respect to each other, as designed in the 3d model. The theoretical connections were then routed into copper paths and their positions, distance and width was optimized. 
    

![Untitled](SRIP%20Final%20Report%20355d48071ea740b4b49a7ed5b7c8418f/Untitled%202.png)

- PCB Milling
    
    Firstly, we uploaded the BRD (Board) file, generated from our PCB design software, to the Bantam Desktop PCB Milling Machine. We meticulously selected the appropriate tools for the milling process, utilizing a PCB Engraving bit with a width of 0.005" for fine details and a Flat End Mill with a size of 1/32" for precise cuts. With careful attention to calibration and toolpath settings, we initiated the milling process. The Bantam Desktop PCB Milling Machine efficiently and accurately etched the PCB design onto the copper-clad board, resulting in a high-quality PCB ready for assembly.
    

![WhatsApp Image 2023-06-21 at 20.49.42.jpeg](SRIP%20Final%20Report%20355d48071ea740b4b49a7ed5b7c8418f/WhatsApp_Image_2023-06-21_at_20.49.42.jpeg)

- Power supply
    
    The modules were given power directly through the 3V pin of the NodeMCU, thereby making the whole device run on a single micro usb port connected to either a charger or a power bank. 
    
- Integration & Assembly
    
    After milling the PCB, female header pins were soldered upon the various ports. And the modules got snap-fit into the header pins. This modular approach allows easier assembly and disassembly of the device, and allows replacement of a single component instead of the whole device in case of failure. 
    
    ![WhatsApp Image 2023-06-27 at 03.35.55.jpeg](SRIP%20Final%20Report%20355d48071ea740b4b49a7ed5b7c8418f/WhatsApp_Image_2023-06-27_at_03.35.55.jpeg)
    

### Software Design

In the software design phase of our air quality monitoring system, we focused on creating a robust and user-friendly software architecture. The NodeMCU V3 microcontroller, serving as the central processing unit, was programmed using the Arduino IDE. We designed custom firmware to handle data acquisition from the PMS5003 particulate matter sensor and the DHT11 temperature and humidity sensor. The firmware included protocols for data parsing, formatting, and JSON object creation. Utilizing the built-in Wi-Fi capabilities, we implemented MQTT communication to publish the sensor data to the Mosquitto MQTT broker running on our R-pi server. Additionally, we integrated SPI communication to enable data logging on the SD card module. The software design aimed to ensure seamless real-time data transmission, secure data storage, and easy data visualization using Node-RED's Chart Module. The result was an efficient, comprehensive, and user-friendly software system that facilitated real-time monitoring and visualization of air quality data for our IoT-enabled low-cost air quality monitoring device. Users can conveniently access the live output and visualizations on any web browser, enhancing the system's accessibility and usability.

![Screenshot 2023-07-07 110337.png](SRIP%20Final%20Report%20355d48071ea740b4b49a7ed5b7c8418f/Screenshot_2023-07-07_110337.png)

### Testing and Validation

In the testing and validation phase, we will be employing the DustTrak aerosol monitor as the reference instrument to assess the accuracy and reliability of our air quality monitoring system. The DustTrak is a recognized and widely-used instrument known for its precision in measuring particulate matter concentrations. By comparing the data collected from our IoT-enabled low-cost air quality monitoring device with the readings obtained from the DustTrak, we will ensure the system's performance meets rigorous standards and validate its reliability for real-world applications. The integration of the DustTrak in our testing procedures will provide valuable insights and assurance regarding the accuracy and effectiveness of our air quality monitoring system.

### Results

- Real time visualization
    
    The various particulate matter, temperature and humidity datapoints were visualized in real time via the webpage rendered in the mobile browser. 
    
    ![Untitled](SRIP%20Final%20Report%20355d48071ea740b4b49a7ed5b7c8418f/Untitled%203.png)
    
- Robustness
    
    The device was allowed to run continuously for 24 hours and log data, thus proving its robustness. It was plugged via a micro-usb mobile charger plugged into a wall socket. 
    

### Further Development

In the pursuit of further enhancing the capabilities and reliability of our air quality monitoring device, several notable improvements are planned for future iterations. First and foremost, we aim to incorporate a user-friendly LCD screen, providing real-time visual feedback of the monitored data, enhancing the device's usability and accessibility. Additionally, to ensure redundancy and accurate data validation, we plan to introduce dual Plantower sensors, enabling cross-referencing and error detection. To expand the scope of data analysis and provide location-specific information, a GPS module will be integrated, allowing precise geotagging of data points. Furthermore, in a subsequent iteration, we envision transitioning from NodeMCU's Wi-Fi-based data transmission to GSM-based data transmission. This shift will enable data transfer even in remote areas with limited internet connectivity, enhancing the device's adaptability and reliability for widespread deployment. These advancements will culminate in a more sophisticated and versatile air quality monitoring solution, empowering users with comprehensive, accurate, and location-aware environmental insights for improved decision-making and public health awareness.

### Key highlights

- Our air quality monitoring device offers an affordable and portable solution for accurately measuring particulate matter data, making it accessible for a wider user base.
- The device's versatile power options, including phone chargers, power banks, and batteries, ensure convenient and uninterrupted operation in various settings.
- With a total cost in the range of ₹3000, our device presents a highly cost-effective alternative compared to existing products in the Indian markets, enabling greater affordability and widespread adoption.
- The incorporation of real-time visualization and cloud storage capabilities empowers users to access and analyze air quality data remotely, promoting data-driven decision-making and fostering greater environmental awareness.

### QR to Github repository

![Untitled](SRIP%20Final%20Report%20355d48071ea740b4b49a7ed5b7c8418f/Untitled%204.png)

### References

1. Pandey, A., Brauer, M., Cropper, M. 
L., Balakrishnan, K., Mathur, P., Dey, S., ... & Dandona, L. (2021).
 Health and economic impact of air pollution in the states of India: the
 Global Burden of Disease Study 2019. *The Lancet Planetary Health*, *5*(1), e25-e38.
2. Moreno-Rangel, Alejandro & Sharpe, Tim & Musau, Filbert & Mcgill, Grainne. (2018). Field evaluation of a low-cost indoor air quality monitor to quantify exposure to pollutants in residential environments. Journal of Sensors and Sensor Systems. 7. 10.5194/jsss-7-373-2018.
3. Alfano, Brigida & Barretta, Luigi & Giudice, Antonio & De Vito, Saverio & Francia, Girolamo & Esposito, Elena & Formisano, Fabrizio & Massera, Ettore & Miglietta, Maria Lucia & Polichetti, Tiziana. (2021). Correction: Alfano et al. A Review of Low-Cost Particulate Matter Sensors from the Developers’ Perspectives. Sensors 2020, 20, 6819. Sensors. 21. 3060. 10.3390/s21093060.
4. Li, J. and Biswas, P. (2017). Optical Characterization Studies of a Low-Cost Particle Sensor. *Aerosol Air Qual. Res.* 17: 1691-1704. https://doi.org/10.4209/aaqr.2017.02.0085
5. Bulot, F.M.J., Johnston, S.J., Basford, P.J. *et al.* Long-term field comparison of multiple low-cost particulate matter sensors in an outdoor urban environment.
    
    *Sci Rep* **9**, 7497 (2019). https://doi.org/10.1038/s41598-019-43716-3