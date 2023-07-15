-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Mar 31, 2023 at 04:50 PM
-- Server version: 10.4.27-MariaDB
-- PHP Version: 8.2.0

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `silent spaces`
--

-- --------------------------------------------------------

--
-- Table structure for table `criteria`
--

CREATE TABLE `criteria` (
  `criteria_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `noise_level` int(11) NOT NULL,
  `capacity` int(11) NOT NULL,
  `rating` int(11) NOT NULL,
  `connectivity` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `locations`
--

CREATE TABLE `locations` (
  `space_id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `address` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `locations`
--

INSERT INTO `locations` (`space_id`, `name`, `address`) VALUES
(1, 'UIC SELE', '950 S Halsted St'),
(2, 'UIC SELW', '950 S Halsted St'),
(3, 'UIC SCE', '750 S Halsted St'),
(4, 'UIC ARC', '507 S Morgan St');

-- --------------------------------------------------------

--
-- Table structure for table `reviews`
--

CREATE TABLE `reviews` (
  `space_id` int(11) NOT NULL,
  `room_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `room`
--

CREATE TABLE `room` (
  `room_id` int(11) NOT NULL,
  `space_id` int(11) NOT NULL,
  `tables` int(11) NOT NULL,
  `people` int(11) NOT NULL,
  `access` int(11) NOT NULL,
  `booths` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `space`
--

CREATE TABLE `space` (
  `space_id` int(11) NOT NULL,
  `room_id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `address` varchar(255) NOT NULL,
  `noise_level` int(11) NOT NULL,
  `connectivity` int(11) NOT NULL,
  `hours_of_operation` time NOT NULL,
  `rating` int(11) NOT NULL,
  `capacity` int(11) NOT NULL,
  `reviews` varchar(255) NOT NULL,
  `access` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `spaces`
--

CREATE TABLE `spaces` (
  `space_id` int(11) NOT NULL,
  `area_id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `address` varchar(255) NOT NULL,
  `noise_level` int(11) NOT NULL,
  `connectivity_level` int(11) NOT NULL,
  `open_time` time NOT NULL,
  `close_time` time NOT NULL,
  `rating` int(11) NOT NULL,
  `capacity` int(11) NOT NULL,
  `access` int(11) NOT NULL,
  `reviews` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `spaces`
--

INSERT INTO `spaces` (`space_id`, `area_id`, `name`, `address`, `noise_level`, `connectivity_level`, `open_time`, `close_time`, `rating`, `capacity`, `access`, `reviews`) VALUES
(1, 1, 'UIC SELE', '950 S Morgan St', 40, 90, '07:00:00', '07:00:00', 8, 1000, 1, 'Good place to relax and study'),
(2, 2, 'UIC SELW', '950 S Halsted St', 50, 95, '07:00:00', '07:00:00', 8, 1000, 1, 'Not noisy'),
(3, 3, 'UIC SCE', '750 S Halsted st', 60, 80, '06:00:00', '10:00:00', 7, 500, 0, 'Can get crowded and noisy'),
(4, 4, 'UIC ARC', '507 S Morgan st', 55, 85, '07:00:00', '08:00:00', 9, 1000, 1, 'Quiet but not a lot of spots');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `user_id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `reviews` varchar(255) NOT NULL,
  `ratings` int(11) NOT NULL,
  `criteria_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `locations`
--
ALTER TABLE `locations`
  ADD PRIMARY KEY (`space_id`);

--
-- Indexes for table `spaces`
--
ALTER TABLE `spaces`
  ADD PRIMARY KEY (`area_id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`user_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `locations`
--
ALTER TABLE `locations`
  MODIFY `space_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT for table `spaces`
--
ALTER TABLE `spaces`
  MODIFY `area_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `user_id` int(11) NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
