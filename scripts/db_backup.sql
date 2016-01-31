-- MySQL dump 10.16  Distrib 10.1.11-MariaDB, for Linux (x86_64)
--
-- Host: 127.0.0.1    Database: notedb
-- ------------------------------------------------------
-- Server version	10.1.11-MariaDB-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `notes`
--

DROP TABLE IF EXISTS `notes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `notes` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `Content` mediumtext NOT NULL,
  `Timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=26 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `notes`
--

LOCK TABLES `notes` WRITE;
/*!40000 ALTER TABLE `notes` DISABLE KEYS */;
INSERT INTO `notes` VALUES (1,'Hello','2030-01-15 23:39:06'),(2,'Testing new clientmanager #dev','2030-01-15 23:39:06'),(3,'hello#tele','2029-01-16 13:29:07'),(4,'I am getting a bit tired.#ozstuff #tired','2029-01-16 13:27:28'),(5,'Testnote  #yolo','2030-01-15 23:05:34'),(6,'This is a test note.#vim #cool','2029-01-16 13:24:04'),(7,'VIm is a pretty cool thing\n#vim #prog #cool','2024-01-16 07:17:10'),(8,'Final testnote before refactoring entire project.\n#final','2026-01-16 00:45:06'),(9,'This is a good note.','2023-01-15 23:57:57'),(10,'A note about nmap, i want to learn this better. #nmap','2024-01-16 07:18:31'),(11,'inotify-tools is a library which allows for software to monitor for file changes, and directory \nchanges. \n\n#sysdev #notedb','2025-01-16 12:38:45'),(12,'Another development testnote #dev','2030-01-16 06:54:52'),(13,'Maybe its also time to start looking at haskell. #prog','2024-01-16 07:21:54'),(14,'this is temponote #yolo','2026-01-16 08:52:27'),(15,'Hall[!!!! hej','2022-01-16 12:48:41'),(16,'testing#asd#qwe','2029-01-16 13:29:35'),(17,'Last note before my commit.','2023-01-16 00:04:49'),(18,'Hello world #programming','2030-01-15 23:19:08'),(19,'Expand logger to be async, using a ringbuffer and threads. #notedb','2031-01-16 00:32:21'),(20,'hello oh almighty world','2029-01-16 13:01:23'),(21,'git add -p \nchoose which hunks of data from a file to stage\n#git','2025-01-16 09:25:41'),(22,'testing #yolo','2031-01-16 12:11:52'),(23,'I want to sleep right now. #tired','2031-01-16 12:18:59'),(24,'bla bla ohej #yolo','2031-01-16 12:20:32'),(25,'Jag är trött #sova','2031-01-16 12:21:19');
/*!40000 ALTER TABLE `notes` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-01-31 22:33:02
