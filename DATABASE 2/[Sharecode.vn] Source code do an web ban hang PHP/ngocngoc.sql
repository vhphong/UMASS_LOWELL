-- phpMyAdmin SQL Dump
-- version 3.1.3.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jun 11, 2010 at 01:17 PM
-- Server version: 5.1.33
-- PHP Version: 5.2.9-2

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `ngocngoc`
--
CREATE DATABASE `ngocngoc` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;
USE `ngocngoc`;

-- --------------------------------------------------------

--
-- Table structure for table `loaisp`
--

CREATE TABLE IF NOT EXISTS `loaisp` (
  `maloai` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `ten` varchar(100) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`maloai`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `loaisp`
--

INSERT INTO `loaisp` (`maloai`, `ten`) VALUES
('l1', 'HonDa'),
('l2', 'MazDa'),
('l3', 'Toyota'),
('l4', 'Dewoo'),
('l5', 'Ferrari'),
('l6', 'BMW');

-- --------------------------------------------------------

--
-- Table structure for table `mathang`
--

CREATE TABLE IF NOT EXISTS `mathang` (
  `tenhang` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `mahang` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  `username` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `ngaymua` date NOT NULL,
  `soluong` int(15) NOT NULL,
  `kieu` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`mahang`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `mathang`
--


-- --------------------------------------------------------

--
-- Table structure for table `sanpham`
--

CREATE TABLE IF NOT EXISTS `sanpham` (
  `mahang` int(20) NOT NULL AUTO_INCREMENT,
  `tenhang` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `giatien` int(20) NOT NULL,
  `kieu` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  `maloai` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `sogr1sp` int(5) NOT NULL,
  `sosp1thung` int(5) NOT NULL,
  `hinhanh` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`mahang`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=65 ;

--
-- Dumping data for table `sanpham`
--

INSERT INTO `sanpham` (`mahang`, `tenhang`, `giatien`, `kieu`, `maloai`, `sogr1sp`, `sosp1thung`, `hinhanh`) VALUES
(36, 'HonDa CRV', 60000, '4 cho', 'l1', 1, 1, 'CRV.jpg'),
(37, 'skydeck', 25000, '4cho', 'l1', 1, 1, 'skydeck.jpeg'),
(40, 'lead', 2000, '2 banh', 'l1', 1, 1, 'lead.jpeg'),
(43, 'mazda3', 40000, '4 cho', 'l2', 1, 1, 'mazda3.jpeg'),
(44, 'mazda6', 43000, '4 cho', 'l2', 1, 1, 'mazda6.jpeg'),
(45, 'mazda9', 60000, '4 cho', 'l2', 1, 1, 'mazda9.jpeg'),
(46, 'camry', 36000, '4 cho', 'l3', 1, 1, 'camry.jpeg'),
(47, 'vios', 29000, '4 cho', 'l3', 1, 1, 'vios.jpeg'),
(48, 'corola', 27000, '4 cho', 'l3', 1, 1, 'corola.jpeg'),
(49, 'altis', 33000, '4 cho', 'l3', 1, 1, 'atis.jpeg'),
(50, 'Q7', 52000, '4 cho', 'l3', 1, 1, 'q7.jpeg'),
(51, 'matiz', 19000, '4 cho', 'l4', 1, 1, 'matiz.jpeg'),
(52, 'sinai', 26000, '4 cho', 'l4', 1, 1, 'sinai.jpeg'),
(53, 'f430', 90000, '2 cho', 'l5', 1, 1, 'f430.jpeg'),
(54, 'enzo', 120000, '2 cho', 'l5', 1, 1, 'enzo.jpeg'),
(55, 'california', 135000, '2 cho', 'l5', 1, 1, 'california.jpeg'),
(56, 'spider', 150000, '2 cho', 'l5', 1, 1, 'spider.jpeg'),
(57, '599', 300000, '2 cho', 'l5', 1, 1, '599.jpeg'),
(58, 'seri3', 69000, '4 cho', 'l6', 1, 1, 'seri3.jpeg'),
(60, 'seri5', 69000, '4 cho', 'l6', 1, 1, 'seri5.jpeg'),
(61, 'x6', 65000, '4 cho', 'l6', 1, 1, 'x6.jpeg'),
(62, 'Sh', 2000, '2 banh', 'l1', 0, 0, 'SH.jpeg'),
(63, 'civic', 45000, '4 banh', 'l1', 0, 0, 'civic.jpg'),
(64, 'PS', 30000, '2 banh', 'l1', 0, 0, 'PS.jpeg');

-- --------------------------------------------------------

--
-- Table structure for table `thanhvien`
--

CREATE TABLE IF NOT EXISTS `thanhvien` (
  `hoten` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `ngaysinh` date DEFAULT NULL,
  `quequan` varchar(30) COLLATE utf8_unicode_ci DEFAULT NULL,
  `dienthoai` int(15) NOT NULL,
  `username` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `password` int(20) NOT NULL,
  `quyen` varchar(1) COLLATE utf8_unicode_ci NOT NULL DEFAULT '0',
  PRIMARY KEY (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `thanhvien`
--

INSERT INTO `thanhvien` (`hoten`, `ngaysinh`, `quequan`, `dienthoai`, `username`, `password`, `quyen`) VALUES
('tuananh', '1986-02-22', 'Ha noi', 916012274, 'admin', 123456, '1'),
('Admin', '1988-09-06', 'Ha noi', 982735387, 'Ngoc', 123456, '1'),
('Ngoc', '1989-05-26', 'Ha noi', 982735387, 'ngocngoc', 123456, '0'),
('Doan Quoc Khanh', '1988-11-09', 'Ha noi', 984523264, 'qk_quockhanh', 123456, '0'),
('tuananh', '1980-01-01', 'Ha noi', 321651, 'tuananh', 123456, '0');
